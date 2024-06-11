import glob
import os

# Set the URL of the GitHub repository
github_repo_url = "https://github.com/silash35/silash35.github.io.git"


# Clone or update the repository
repo_folder = github_repo_url.split("/")[-1][:-4]
os.makedirs("repos", exist_ok=True)

if os.path.exists("repos/" + repo_folder):
    os.system(f"cd repos/{repo_folder} && git pull")
else:
    os.system("cd repos && git clone " + github_repo_url)


# Get a list of all files in the repository
files = glob.glob(f"repos/{repo_folder}/**/*.*", recursive=True)


# Setup splitters
import json
from langchain_text_splitters import (
    Language,
    RecursiveCharacterTextSplitter,
    RecursiveJsonSplitter,
)

javascript_splitter = RecursiveCharacterTextSplitter.from_language(
    language=Language.JS, chunk_size=1000, chunk_overlap=100
)

typescript_splitter = RecursiveCharacterTextSplitter.from_language(
    language=Language.TS, chunk_size=1000, chunk_overlap=100
)

css_splitter = RecursiveCharacterTextSplitter(
    separators=["\n\n.", "\n\n#", "\n\n", "\n", " ", ""],
    chunk_size=1000,
    chunk_overlap=50,
    length_function=len,
    is_separator_regex=False,
)

json_splitter = RecursiveJsonSplitter(max_chunk_size=1000)


# Helper function to print chunks
def print_chunks(chunks):
    for chunk in chunks:
        print("----------------------------------------------")
        print(chunk)
        print("----------------------------------------------")


# Generate chunks
for file in files:
    if file.endswith(".js") or file.endswith(".jsx"):
        with open(file, "r") as f:
            content = f.read()
            print_chunks(javascript_splitter.split_text(content))

    if file.endswith(".ts") or file.endswith(".tsx"):
        with open(file, "r") as f:
            content = f.read()
            print_chunks(typescript_splitter.split_text(content))

    if file.endswith(".css") or file.endswith(".scss"):
        with open(file, "r") as f:
            content = f.read()
            print_chunks(css_splitter.split_text(content))

    if file.endswith(".json"):
        with open(file, "r") as f:
            content = json.load(f)
            print_chunks(json_splitter.split_json(content))
