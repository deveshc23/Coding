import json

# 1. Read the JSON data
with open('viz_data.json', 'r', encoding='utf-8') as f:
    data = f.read()

# 2. Read the HTML template
with open('bl_viz.html', 'r', encoding='utf-8') as f:
    html = f.read()

# 3. Inject the data into the HTML
html = html.replace('const RAW = __VIZ_DATA__;', f'const RAW = {data};')

# 4. Save the final playable HTML file
with open('bl_backtest.html', 'w', encoding='utf-8') as f:
    f.write(html)

print("Dashboard built successfully! Open 'bl_backtest.html' in your browser.")