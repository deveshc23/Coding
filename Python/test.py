from pandas.io.stata import StataReader
import pandas as pd
#reader = StataReader(r'C:\Users\choud\OneDrive\Desktop\Coding\UP_BH_Individual_UDAYA 2_30102020.dta')
data = pd.read_stata(r'C:\Users\choud\OneDrive\Desktop\Coding\UP_BH_Individual_UDAYA 2_30102020.dta', convert_categoricals=False)
print(data)