import pandas as pd

# Path to the Stata file
stata_file_path = r'C:\Users\choud\OneDrive\Desktop\Coding\UP_BH_Individual_UDAYA 2_30102020.dta'

# Path to save the CSV file
csv_file_path = r'C:\Users\choud\OneDrive\Desktop\Coding\Data_for_2018-19.csv'

try:
    # Read the Stata file
    data = pd.read_stata(stata_file_path, convert_categoricals=False)

    # Save the data to a CSV file
    data.to_csv(csv_file_path, index=False)  # 'index=False' avoids adding a default index column

    # Print a success message and the first few rows of the DataFrame
    print("Data successfully saved to CSV!")
    print(data.head())  # Display the first few rows

except FileNotFoundError:
    print(f"File not found: {stata_file_path}")
except Exception as e:
    print(f"An error occurred: {e}")
