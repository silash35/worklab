from langchain_huggingface import HuggingFaceEndpoint
from dotenv import load_dotenv

load_dotenv()

model = HuggingFaceEndpoint(repo_id="meta-llama/Meta-Llama-3-8B-Instruct", task="text-generation")  # type: ignore

questions = [
    """Código limpo refere-se a um estilo de programação que enfatiza a clareza, legibilidade e manutenibilidade do código fonte.
Cite 5 benefícios de se utilizar o Clean Code (código limpo) no desenvolvimento de software.
Utilize tópicos curtos.""",
    """Como algum desses benefícios pode melhor o seguinte código?
Mostre como ele poderia ser melhorado utilizando algum dos benefícios listados. Utilize apenas 1 benefício.

def calc_average(scores):
    total = 0
    count = 0
    for score in scores:
        total = total + score
        count = count + 1
    average = total / count
    return average

grades = [90, 85, 95, 87, 92]
print("The average grade is:", calc_average(grades))
""",
]

history = ""

for question in questions:
    prompt = f"""<|begin_of_text|>

<|start_header_id|>system<|end_header_id|>
Você é um assistente especialista em programação.
Você vai auxiliar o usuário respondendo as perguntas dele e ajudando ele nas tarefas que ele pedir.
Sempre responda o que ele pedir.
<|eot_id|>

{history}

<|start_header_id|>user<|end_header_id|>
{question}
<|eot_id|>

<|start_header_id|>assistant<|end_header_id|>
"""

    response = model.invoke(prompt)

    # Adicione a pergunta e a resposta ao histórico
    history += f"""
<|start_header_id|>user<|end_header_id|>
{question}
<|eot_id|>
"""

    history += f"""
<|start_header_id|>assistant<|end_header_id|>
{response}
<|eot_id|>
"""

    # Imprima a pergunta e a resposta
    print("User: " + question)
    print("Assistant: " + response)


# Conversa com o assistente na integra:

# User: Código limpo refere-se a um estilo de programação que enfatiza a clareza, legibilidade e manutenibilidade do código fonte.
# Cite 5 benefícios de se utilizar o Clean Code (código limpo) no desenvolvimento de software.
# Utilize tópicos curtos.
# Assistant: Aqui estão 5 benefícios de se utilizar o Clean Code no desenvolvimento de software:

# • **Legibilidade**: Código fácil de ler e entender, o que facilita a manutenção e o desenvolvimento do software.

# • **Manutenção**: Código limpo é mais fácil de manter e atualizar, pois sua estrutura e organização são claras e coerentes.

# • **Desenvolvimento**: Código limpo ajuda a desenvolver software de forma mais eficiente, pois os desenvolvedores podem entender melhor o que está sendo feito e trabalhar em equipe de forma mais eficaz.

# • **Redução de bugs**: Código limpo é mais fácil de testar e debugar, pois sua estrutura e lógica são claras e fáceis de entender.

# • **Melhora da produtividade**: Código limpo permite que os desenvolvedores trabalhem mais rapidamente e eficazmente, pois não precisam se preocupar com a complexidade e a confusão do código.
# User: Como algum desses benefícios pode melhor o seguinte código?
# Mostre como ele poderia ser melhorado utilizando algum dos benefícios listados. Utilize apenas 1 benefício.

# def calc_average(scores):
#     total = 0
#     count = 0
#     for score in scores:
#         total = total + score
#         count = count + 1
#     average = total / count
#     return average

# grades = [90, 85, 95, 87, 92]
# print("The average grade is:", calc_average(grades))

# Assistant: Um exemplo de código que pode ser melhorado utilizando o benefício da "Legibilidade".

# Aqui está o código melhorado:
# ```
# def calculate_average(scores):
#     """
#     Calculate the average score from a list of scores.
#     :param scores: A list of scores
#     :return: The average score
#     """
#     return sum(scores) / len(scores)

# grades = [90, 85, 95, 87, 92]
# print("The average grade is:", calculate_average(grades))
# ```
# Nesse exemplo, o código foi melhorado da seguinte forma:

# * O nome da função foi alterado para `calculate_average`, tornando-o mais descritivo e fácil de entender.
# * A função `sum` e `len` foram utilizadas em vez de variáveis `total` e `count`, tornando o código mais conciso e fácil de ler.
# * A função agora tem um comentário que descreve o que ela faz, tornando-a mais fácil de entender para outros desenvolvedores.

# Essas alterações melhoraram a legibilidade do código, tornando-o mais fácil de entender e manter.
