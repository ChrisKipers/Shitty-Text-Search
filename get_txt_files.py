# Retreives all books from www.textfiles.com/etext as text data for full text search engine.
# Run time is between 5 and 10 minutes.

import requests
from bs4 import BeautifulSoup
import os
import itertools

DIR_TO_SAVE_BOOKS = os.path.join(os.path.dirname(os.path.realpath(__file__)), 'books')

BOOK_CATEGORIES = ['MODERN', 'FICTION', 'NONFICTION', 'REFERENCE']
BASE_URL = 'http://www.textfiles.com/etext'

def get_text_urls(category_url):
    html_text = requests.get(category_url).text
    soup = BeautifulSoup(html_text, 'html.parser')
    rows = soup.find_all('tr')
    # Skip the first row and the last row
    return [get_row_info(row, category_url) for row in rows[1:-1]]

def get_row_info(row, category_url):
    columns = row.find_all('td')
    url = columns[0].a['href']
    title = columns[2].get_text()
    return category_url + '/' + url, title

def save_book(row_info):
    url, title = row_info
    book_content = requests.get(url).text
    book_file_path = os.path.join(DIR_TO_SAVE_BOOKS, title[:20].replace(' ', '_'))
    with open(book_file_path, 'w') as text_file:
        text_file.write(book_content.encode('utf8'))

nested_row_items = [get_text_urls(BASE_URL + '/' + category) for category in BOOK_CATEGORIES]
flat_row_items = [item for sublist in nested_row_items for item in sublist]
[save_book(row_info) for row_info in flat_row_items]