from langchain_community.document_loaders import PyPDFLoader
from langchain_openai import OpenAIEmbeddings
from langchain_chroma import Chroma
from langchain_core.documents import Document
from langchain_text_splitters import RecursiveCharacterTextSplitter

from dotenv import load_dotenv

load_dotenv()

text_splitter = RecursiveCharacterTextSplitter(
    separators=[
        "\n\n",
        "\n",
        ".",
        "!",
        "?",
        ";",
        "—",
        " ",
        "",
    ],
    chunk_size=1000,
    chunk_overlap=200,
    length_function=len,
    is_separator_regex=False,
)

import glob

files = glob.glob("./pdfs/*")

chunks = []

for file in files:
    print(file)
    loader = PyPDFLoader(file)
    pages = loader.load()  # devolve um Document, envelopando a string
    pages = [page.page_content for page in pages]  # tiro a string de dentro do document
    chunks = chunks + text_splitter.split_text("\n".join(pages))
    print(len(chunks))

print(len(chunks))
print(chunks[100])

docs = [Document(page_content=chunk) for chunk in chunks]

db = Chroma.from_documents(docs, OpenAIEmbeddings(), persist_directory="./tomorrow")
