from bs4 import BeautifulSoup
SIMPLE_HTML='''<html>
<head></head>
<body>
<h1>This is a title</h1>
<p class="subtitle">Blah Blah</p>
<p> Here is another p without a class</p>
<ul>
   <li>Rolf</li>
   <li>Charlie</li>
   <li>Jen</li>
   <li>Jose</li>
</body>
'''
simple_soup=BeautifulSoup(SIMPLE_HTML,'html.parser')
def find_title():
    print(simple_soup.find('h1').string)
"""This is how you find the tile in any html file
   First use the parser for the variable to understand what
   is written in HTML and then you can search any thing you want in the entire html file"""
def find_list_items():
    list_items=simple_soup.findAll('li')
    list_contents=[e.string for e in list_items]
    print(list_contents)

def find_subtitle():
    paragraph=simple_soup.find('p',{'class':'subtitle'})
    print(paragraph.string)

def find_all_para():
    paragraph=simple_soup.findAll('p')
    para_contents=[e.string for e in paragraph]
    print(para_contents)

def find_other_paragraph():
    para = simple_soup.findAll('p')
    other_para = [p for p in para if 'subtitle' not in p.attrs.get('class', [])]
    print(other_para[0].string)
"""if you don't find the attribute class in p then instead of
 returning None, you return an empty list hence the ('class',[])"""
find_title()
find_list_items()
find_subtitle()
find_other_paragraph()