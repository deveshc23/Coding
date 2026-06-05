class QuoteLocators:
    AUTHOR='small.author'
    CONTENT='span.text'
    TAGS='div.tags a.tag'
class QuoteParser:
    """Given one of the specific quote divs, find out the data given about the quote"""
    def __init__(self,parent):
        self.parent=parent

    @property
    def content(self):
        locator=QuoteLocators.CONTENT
        return self.parent.select_one(locator).string

    @property
    def author(self):
        locator=QuoteLocators.AUTHOR
        return self.parent.select_one(locator).string

    @property
    def tags(self):
        locator=QuoteLocators.TAGS
        return [e.string for e in self.parent.select(locator)]

    def __repr__(self):
        return f'Quote {self.content}, by {self.author}'



