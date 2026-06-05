import pandas as pd
import re
from rapidfuzz import fuzz

f1=pd.read_csv("file1.csv")
f2=pd.read_csv("file2.csv")

def norm_gender(g):
    if pd.isna(g):
        return None
    g=str(g).strip().lower()
    if g in {"m"}:
        return "M"
    if g in {"f"}:
        return "F"
    return None

titles_to_remove=[
    r'\bdr\b', r'\bmr\b', r'\bms\b', r'\bmrs\b', r'\bprof\b'
]
bad_names={"na", "n/a", "null", "none", "test", "dummy", "-", ".", "--"}

def comprehensive_clean_name(name):
    if pd.isna(name):
        return ""
    name=str(name).lower()
    if ',' in name:
        name=name.split(',')[0]
    title_pattern=r'|'.join(titles_to_remove)
    name=re.sub(title_pattern, '', name)
    name=re.sub(r'[^a-z\s]', ' ', name)
    name=re.sub(r'\s+', ' ', name).strip()
    if name in bad_names:
        return ""
    return name

def calculate_match_score(name1, name2, gender1, gender2):
    name_score=fuzz.ratio(name1, name2)
    gender_adjustment=0
    if gender1 and gender2:
        if gender1==gender2:
            gender_adjustment=10
        else:
            gender_adjustment=-25
    return name_score+gender_adjustment

f1['clean_name']=f1['name'].apply(comprehensive_clean_name)
f1['gender_n']=f1['gender'].apply(norm_gender)
f2['clean_name']=f2['name'].apply(comprehensive_clean_name)
f2['gender_n']=f2['gender'].apply(norm_gender)

f1_cleaned=f1[f1['clean_name'].str.len()>2].copy()
f2_cleaned=f2[f2['clean_name'].str.len()>2].copy()

results=[]
SCORE_THRESHOLD=50

for index1, row1 in f1_cleaned.iterrows():
    q_name=row1['clean_name']
    q_gender=row1['gender_n']
    best_score=-100
    best_match_row=None
    for index2, row2 in f2_cleaned.iterrows():
        c_name=row2['clean_name']
        c_gender=row2['gender_n']
        score=calculate_match_score(q_name, c_name, q_gender, c_gender)
        if score>best_score:
            best_score=score
            best_match_row=row2
    if best_match_row is not None and best_score>=SCORE_THRESHOLD:
        results.append({
            'f1_id': row1['id'],
            'f1_name': row1['name'],
            'f1_gender': row1['gender'],
            'f2_id_match': best_match_row['id'],
            'f2_name_match': best_match_row['name'],
            'f2_gender_match': best_match_row['gender'],
            'final_score': round(best_score)
        })
    else:
        results.append({
            'f1_id': row1['id'],
            'f1_name': row1['name'],
            'f1_gender': row1['gender'],
            'f2_id_match': None,
            'f2_name_match': None,
            'f2_gender_match': None,
            'final_score': 0
        })

match_df=pd.DataFrame(results)
match_df.sort_values(by='final_score', ascending=False, inplace=True)
output_filename="matches_with_gender.csv"
match_df.to_csv(output_filename, index=False)