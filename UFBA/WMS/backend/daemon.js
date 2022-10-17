// import Readline from "@serialport/parser-readline";
import * as dotenv from "dotenv";
import nodemailer from "nodemailer";
import { SerialPort } from "serialport";
dotenv.config();

const port = new SerialPort({ path: "/dev/ttyUSB0", baudRate: 115200 });
// const parser = port.pipe(new Readline({ delimiter: "\n" })); // Read the port data

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

port.on("data", (data) => {
  console.log("[Arduino] ", data);

  let text = data;

  transporter
    .sendMail({
      from: `"Arduino" <${process.env.EMAIL_USER}>`,
      to: `${process.env.EMAIL_USER}, ${"silash35@gmail.com"}`,
      subject: "Atualizações sobre o seu equipamento",

      text,
    })
    .then(() => {
      console.log("Email enviado com sucesso");
    });
});
