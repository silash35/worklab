from langchain_core.prompts import ChatPromptTemplate
from langchain_openai import ChatOpenAI
from chromadb.utils.embedding_functions import OpenAIEmbeddingFunction
import chromadb
import os
from sentence_transformers import CrossEncoder

from dotenv import load_dotenv

load_dotenv()


def select_similar_chunks(user_query):
    client = chromadb.PersistentClient(path="./tomorrow")
    col = client.get_or_create_collection(
        "langchain",
        embedding_function=OpenAIEmbeddingFunction(api_key=os.getenv("OPENAI_API_KEY")),  # type: ignore
    )
    results = col.query(query_texts=[user_query], n_results=10)
    return results["documents"][0]  # type: ignore


messages = [
    (
        "system",
        "Quero que você atue como um expert em livros de ficção juvenil.",
    ),
    ("system", "Sempre responda em até 150 palavras."),
]


def prompt_llm(user_query, extra_info):
    model = ChatOpenAI()
    messages.append(("user", user_query))
    messagesWithInfo = messages + [
        (
            "system",
            f"O texto a seguir é um trecho de um livro que pode ser útil: {extra_info}. Se limite a responder com base nessas informações fornecidas. Tente não trazer outras informações na sua resposta.",
        )
    ]
    prompt = ChatPromptTemplate.from_messages(messagesWithInfo)
    chain = prompt | model

    response = chain.invoke({}).content
    messages.append(("assistant", response))
    return response


rank_model = CrossEncoder("cross-encoder/ms-marco-MiniLM-L-6-v2")


while True:
    user_query = input("Usuário: ")

    if user_query == "exit":
        break

    chunks = select_similar_chunks(user_query)

    print("-------------------------------")
    print("Chunks obtidos:")
    print(chunks)

    print("-------------------------------")
    print("Chunks após ReRank:")
    ranks = rank_model.rank(user_query, chunks)

    filtered_chunks = []
    for i in range(3):
        filtered_chunks.append(chunks[int(ranks[i]["corpus_id"])])

    print(filtered_chunks)
    print("-------------------------------")

    response = prompt_llm(user_query, filtered_chunks)
    print("Bot:", response)
