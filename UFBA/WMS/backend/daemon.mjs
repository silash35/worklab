import * as dotenv from "dotenv";
import nodemailer from "nodemailer";
import { ReadlineParser, SerialPort } from "serialport";
dotenv.config();

const port = new SerialPort({
  path: "/dev/ttyUSB0",
  baudRate: 115200,
});

const parser = port.pipe(new ReadlineParser("\n"));

port.on("open", () => {
  console.log("Porta Serial Aberta (Arduíno conectado com sucesso)");
});

const transporter = nodemailer.createTransport({
  host: process.env.EMAIL_HOST,
  port: 587,
  secure: false,
  auth: {
    user: process.env.EMAIL_USER,
    pass: process.env.EMAIL_PASSWORD,
  },
});

parser.on("data", (data) => {
  console.log("[Arduino] ", data);

  let text = data;

  if (text.startsWith("mat:")) {
    transporter
      .sendMail({
        from: `"Arduino" <${process.env.EMAIL_USER}>`,
        to: `${process.env.EMAIL_USER}, ${"silash35@gmail.com"}`,
        subject: "A esteira transportadora de resíduos precisa de sua atenção",
        text: text.slice(5),
      })
      .then(() => {
        console.log("Email enviado com sucesso para o operador da esteira");
      })
      .catch(() => {
        console.log("Um Erro ocorreu ao enviar Email para o operador da esteira");
      });
  }

  if (text.startsWith("truck: ")) {
    transporter
      .sendMail({
        from: `"Arduino" <${process.env.EMAIL_USER}>`,
        to: `${process.env.EMAIL_USER}, ${"silash35@gmail.com"}`,
        subject: "Container cheio",
        text: text.slice(7),
      })
      .then(() => {
        console.log("Email enviado com sucesso para o motorista do caminhão");
      })
      .catch(() => {
        console.log("Um Erro ocorreu ao enviar Email para o motorista do caminhão");
      });
  }
});
