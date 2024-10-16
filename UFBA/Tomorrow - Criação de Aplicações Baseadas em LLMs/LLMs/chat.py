from langchain_core.prompts import ChatPromptTemplate
from langchain_openai import ChatOpenAI
from langchain_community.document_loaders import PyPDFLoader
from youtube_transcript_api import YouTubeTranscriptApi
from dotenv import load_dotenv

load_dotenv()


def get_link_info(url):
    if url.startswith("https://www.youtube.com/watch?v="):
        video_id = url.split("=")[1]
        transcript = YouTubeTranscriptApi.get_transcript(video_id, languages=["pt-BR"])
        lines = [line["text"] for line in transcript]
        return "\n".join(lines)  # converto a lista de strings para uma única string

    loader = PyPDFLoader(url)
    pages = loader.load()  # devolve um Document, envelopando a string
    pages = [page.page_content for page in pages]  # tiro a string de dentro do document
    return "\n".join(pages)  # converto a lista de strings para uma única string


model = ChatOpenAI(model="gpt-3.5-turbo")

prompt = ChatPromptTemplate.from_messages(
    [
        (
            "system",
            "Quero que você responda usando apenas o conhecimento obtido pelas informações disponibilizadas abaixo.",
        ),
        ("user", "{user_query}"),
        (
            "system",
            "Informações disponibilizadas: {context_info}",
        ),
        (
            "system",
            "Responda em até 60 palavras. Caso o usuário pergunte algo fora do contexto das informações disponibilizadas, responda que não sabe.",
        ),
    ]
)

chain = prompt | model

link = input("Cole aqui um link de um video do youtube ou de um pdf: ")
userPrompt = input("Faça sua pergunta ou requisição sobre o conteúdo do link:")

response = chain.invoke(
    {
        "user_query": userPrompt,
        "context_info": get_link_info(link),
    }
)

print(response.content)


# Análise de resultados:

# link: https://www.youtube.com/watch?v=Dld8WBqAH2g
# userPrompt: Faça um resumo do material que eu disponibilizei.
# Resposta do gpt-4o:
#   Para se manter o mais seco possível em um dia chuvoso, você deve se mover rapidamente.
#   A quantidade de chuva que cai sobre você é constante, independentemente da velocidade, mas ao reduzir o tempo na chuva, você minimiza a água recebida na cabeça.
#   Portanto, mova-se rápido para sair da chuva.
# Resposta do gpt-3.5-turbo:
#   O texto explica que, ao tentar se manter o mais seco possível em dias chuvosos, o ideal é sair da chuva o mais rápido possível, pois a quantidade de água que cai sobre a cabeça é constante, independente da velocidade de deslocamento.
#   Correr ou andar não faz diferença nesse aspecto.

# link: https://s3.novatec.com.br/sumarios/sumario-9788575224144.pdf
# userPrompt: O que é um Commit?
# Resposta do gpt-4o:
#   Um commit é uma ação no Git que salva as alterações feitas no código em um repositório.
#   Ele captura o estado atual do projeto, permitindo que você acompanhe o histórico de mudanças e colabore com outros desenvolvedores.
# Resposta do gpt-3.5-turbo:
#   Commit é a ação de salvar as alterações feitas em um repositório Git.
#   Ao realizar um commit, as modificações são registradas e associadas a uma mensagem que descreve as mudanças realizadas.
#   Cada commit representa um ponto na história do projeto e permite rastrear as modificações ao longo do tempo.
