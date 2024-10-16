import * as dotenv from "dotenv";
import nodemailer from "nodemailer";
import { ReadlineParser, SerialPort } from "serialport";
dotenv.config();

// Iniciar porta serial
const port = new SerialPort({
  path: "/dev/ttyUSB0",
  baudRate: 115200,
});

// Configurar porta para ler cada linha separadamente
const parser = port.pipe(new ReadlineParser("\n"));

// Imprimir na tela sempre que a porta serial conectar
port.on("open", () => {
  console.log("Porta Serial Aberta (Arduíno conectado com sucesso)");
});

// Criar transporter para envio de emails usando variáveis de ambiente.
const transporter = nodemailer.createTransport({
  host: process.env.EMAIL_HOST,
  port: 587,
  secure: false,
  auth: {
    user: process.env.EMAIL_USER,
    pass: process.env.EMAIL_PASSWORD,
  },
});

function delay(time) {
  return new Promise((resolve) => setTimeout(resolve, time));
}

// Executar rotina sempre que dados novos chegarem no serial
parser.on("data", async (text) => {
  // Imprimir na tela mensagem recebida
  console.log("[Arduino] ", text);

  // Variável de controle para repetir o envio de email caso ocorra algum erro
  let retry = false;

  if (text.startsWith("mat:")) {
    // Se a mensagem for pro operador da esteira industrial (mat)

    do {
      try {
        await transporter.sendMail({
          from: `"Arduino" <${process.env.EMAIL_USER}>`,
          to: `${process.env.EMAIL_USER}, ${"silash35@gmail.com"}`,
          subject: "A esteira transportadora de resíduos precisa de sua atenção",
          text: text.slice(5),
        });

        console.log("Email enviado com sucesso para o operador da esteira");
        retry = false;
      } catch (error) {
        console.log(
          "Um Erro ocorreu ao enviar Email para o operador da esteira. Tentando novamente..."
        );
        retry = true;
        await delay(2000);
      }
    } while (retry);
  } else if (text.startsWith("truck: ")) {
    // Se a mensagem for pro operador do caminhão (truck)

    do {
      try {
        await transporter.sendMail({
          from: `"Arduino" <${process.env.EMAIL_USER}>`,
          to: `${process.env.EMAIL_USER}, ${"silash35@gmail.com"}`,
          subject: "Container cheio",
          text: text.slice(7),
        });
        console.log("Email enviado com sucesso para o motorista do caminhão");
        retry = false;
      } catch (error) {
        console.log(
          "Um Erro ocorreu ao enviar Email para o motorista do caminhão. Tentando novamente..."
        );
        retry = true;
        await delay(2000);
      }
    } while (retry);
  }
});
