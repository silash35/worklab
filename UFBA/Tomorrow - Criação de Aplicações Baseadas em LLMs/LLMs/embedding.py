from sentence_transformers import SentenceTransformer
from tabulate import tabulate


model = SentenceTransformer("paraphrase-multilingual-mpnet-base-v2")

chunks = [
    """.page {
  background-color: #ffffff;
  padding: 30px;
  color: #0e0e0e;

  h1 {
    margin-top: 0;
  }

  h3 {
    margin: 0;
  }

  %text {
    font-size: large;
  }

  p {
    @extend %text;
    margin: 5px;
  }

  li {
    @extend %text;
    margin-bottom: 10px;
  }

  small {
    display: block;
    font-size: 0.9em;
  }

  ul {
    margin-top: 6px;
  }

  @media screen and (min-width: 768px) {
    margin: 50px;
    box-shadow: rgb(60 64 67 / 15%) 0px 1px 3px 1px;
    padding: 90px;
  }
}

.background {
  display: contents;

  @media screen and (min-width: 768px) {
    display: block;
    background-color: #d1d1d1;
  }
}
""",
    """import ResumeBody from "@/components/ResumeBody";

import styles from "./content.module.scss";
import Header from "./Header";

const Content = () => (
  <article className={styles.content}>
    <Header />
    <ResumeBody className={styles.body} />
  </article>
);

export default Content;
""",
    """import styles from "./contactCard.module.scss";
import Form from "./Form";
import Social from "./Social";

const ContactCard = () => (
  <article className={styles.card}>
    <section className={styles.grey}>
      <Social />
    </section>
    <section className={styles.orange}>
      <Form />
    </section>
  </article>
);

export default ContactCard;
""",
    """const PortfolioCards = () => (
  <section className={styles.cards}>
    <Card>
      <Card.image alt="Screenshot the OpenSOM demo instance" src="/images/projects/opensom.webp" />
      <Card.content>
        <h2>OpenSOM</h2>
        <p>
          A self-hosted, open source service order manager. With it you can register customers,
          create budgets, send emails and much more.
        </p>
      </Card.content>
      <Card.actions>
        <IconLink
          imgProps={{
            src: "/images/icons/white/link.svg",
            alt: "link icon",
          }}
          linkProps={{
            href: "https://opensom-frontend.silas.eng.br/",
            title: "access the OpenSOM demo instance",
          }}
        />
""",
    """import BundleAnalyzer from "@next/bundle-analyzer";
import CompressionPlugin from "compression-webpack-plugin";
import nextPWA from "next-pwa";
import * as path from "path";
import { fileURLToPath } from "url";

/**
 * @type {import('next').NextConfig}
 */

const withPWA = nextPWA({
  dest: "public",
  disable: process.env.NODE_ENV === "development",
});

const __filename = fileURLToPath(import.meta.url);
""",
    """{'roboticsActivity1': 'Deliver a basic robotics course, teaching automation with Arduino using sensors and actuators.', 'roboticsActivity2': 'Provide support and assistance to students who want to develop their projects, including extracurriculars.', 'roboticsActivity3': 'Clean and organize the robotics laboratory. Including performing the maintenance of the local computers.', 'other': 'Other Things', 'listener': 'listener', 'monitor': 'monitor', 'qtCon': 'QtCon Brazil 2020', 'snct': 'SNCT (National Science and Technology Week) 2019'}""",
]

embeddings = model.encode(chunks)

user_queries = [
    "How do I set a shadow on my website elements using CSS?",
    "How can I build a resume using React, but using semantic HTML tags?",
    "What colors are used on the contact card?",
    "Do you know of any examples of a free service order manager?",
    "I need to analyze the file size of my website made in Next.js. Can you recommend any libraries?",
    "Building a robot sounds like fun, where do I start?",
]
query = model.encode(user_queries)

similarities = model.similarity(query, embeddings).tolist()  # type: ignore


headers = ["", "Chunk 1", "Chunk 2", "Chunk 3", "Chunk 4", "Chunk 5", "Chunk 6"]

similarities[0].insert(0, "Query 1")
similarities[1].insert(0, "Query 2")
similarities[2].insert(0, "Query 3")
similarities[3].insert(0, "Query 4")
similarities[4].insert(0, "Query 5")
similarities[5].insert(0, "Query 6")

print(tabulate(similarities, headers=headers, tablefmt="fancy_grid"))

# Analise de resultados:


# 1. Modelo "all-MiniLM-L6-v2"
# ╒═════════╤═══════════╤════════════╤════════════╤═══════════╤══════════════╤════════════╕
# │         │   Chunk 1 │    Chunk 2 │    Chunk 3 │   Chunk 4 │      Chunk 5 │    Chunk 6 │
# ╞═════════╪═══════════╪════════════╪════════════╪═══════════╪══════════════╪════════════╡
# │ Query 1 │ 0.43509   │  0.118935  │  0.128302  │ 0.137448  │ -0.0984879   │ -0.0507695 │
# ├─────────┼───────────┼────────────┼────────────┼───────────┼──────────────┼────────────┤
# │ Query 2 │ 0.107894  │  0.513456  │  0.349869  │ 0.326201  │  0.127477    │  0.12936   │
# ├─────────┼───────────┼────────────┼────────────┼───────────┼──────────────┼────────────┤
# │ Query 3 │ 0.16753   │  0.0692303 │  0.40181   │ 0.259008  │ -0.098809    │  0.124083  │
# ├─────────┼───────────┼────────────┼────────────┼───────────┼──────────────┼────────────┤
# │ Query 4 │ 0.0909491 │ -0.0629757 │ -0.0515651 │ 0.194051  │ -0.000545382 │  0.15979   │
# ├─────────┼───────────┼────────────┼────────────┼───────────┼──────────────┼────────────┤
# │ Query 5 │ 0.125769  │  0.193243  │  0.114695  │ 0.194471  │  0.480698    │  0.065387  │
# ├─────────┼───────────┼────────────┼────────────┼───────────┼──────────────┼────────────┤
# │ Query 6 │ 0.0436555 │ -0.0394843 │ -0.0249892 │ 0.0348294 │ -0.0378046   │  0.469504  │
# ╘═════════╧═══════════╧════════════╧════════════╧═══════════╧══════════════╧════════════╛

# 2. Modelo "all-mpnet-base-v2"
# ╒═════════╤════════════╤════════════╤════════════╤═══════════╤════════════╤════════════╕
# │         │    Chunk 1 │    Chunk 2 │    Chunk 3 │   Chunk 4 │    Chunk 5 │    Chunk 6 │
# ╞═════════╪════════════╪════════════╪════════════╪═══════════╪════════════╪════════════╡
# │ Query 1 │  0.447621  │  0.237332  │  0.233203  │ 0.183858  │ -0.036421  │ -0.0886261 │
# ├─────────┼────────────┼────────────┼────────────┼───────────┼────────────┼────────────┤
# │ Query 2 │  0.174111  │  0.543403  │  0.331133  │ 0.413034  │  0.102871  │  0.0746877 │
# ├─────────┼────────────┼────────────┼────────────┼───────────┼────────────┼────────────┤
# │ Query 3 │  0.175045  │  0.053054  │  0.432696  │ 0.248325  │ -0.0188333 │  0.0839901 │
# ├─────────┼────────────┼────────────┼────────────┼───────────┼────────────┼────────────┤
# │ Query 4 │  0.0389793 │ -0.0599265 │ -0.0166787 │ 0.0540013 │ -0.0894014 │  0.0925297 │
# ├─────────┼────────────┼────────────┼────────────┼───────────┼────────────┼────────────┤
# │ Query 5 │  0.156257  │  0.161266  │  0.120552  │ 0.169564  │  0.478231  │  0.0494562 │
# ├─────────┼────────────┼────────────┼────────────┼───────────┼────────────┼────────────┤
# │ Query 6 │ -0.03457   │  0.0169253 │  0.01999   │ 0.033837  │ -0.0275201 │  0.352341  │
# ╘═════════╧════════════╧════════════╧════════════╧═══════════╧════════════╧════════════╛

# 3. Modelo "paraphrase-multilingual-mpnet-base-v2"
# ╒═════════╤════════════╤═══════════╤═══════════╤═══════════╤═══════════╤════════════╕
# │         │    Chunk 1 │   Chunk 2 │   Chunk 3 │   Chunk 4 │   Chunk 5 │    Chunk 6 │
# ╞═════════╪════════════╪═══════════╪═══════════╪═══════════╪═══════════╪════════════╡
# │ Query 1 │  0.331811  │ 0.211877  │ 0.191443  │ 0.153775  │ 0.107441  │  0.0204533 │
# ├─────────┼────────────┼───────────┼───────────┼───────────┼───────────┼────────────┤
# │ Query 2 │  0.213064  │ 0.38277   │ 0.323061  │ 0.266929  │ 0.209337  │  0.115309  │
# ├─────────┼────────────┼───────────┼───────────┼───────────┼───────────┼────────────┤
# │ Query 3 │  0.295264  │ 0.0883327 │ 0.369103  │ 0.341748  │ 0.125034  │  0.0366024 │
# ├─────────┼────────────┼───────────┼───────────┼───────────┼───────────┼────────────┤
# │ Query 4 │ -0.0484311 │ 0.0324543 │ 0.0885869 │ 0.23561   │ 0.0134484 │  0.28901   │
# ├─────────┼────────────┼───────────┼───────────┼───────────┼───────────┼────────────┤
# │ Query 5 │  0.271501  │ 0.165497  │ 0.0827782 │ 0.243891  │ 0.396261  │ -0.0403545 │
# ├─────────┼────────────┼───────────┼───────────┼───────────┼───────────┼────────────┤
# │ Query 6 │  0.039519  │ 0.12558   │ 0.0280541 │ 0.0721078 │ 0.077898  │  0.544     │
# ╘═════════╧════════════╧═══════════╧═══════════╧═══════════╧═══════════╧════════════╛
