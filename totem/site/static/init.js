function pedirSenha(){
    let senha = 'nada'
    do{
        senha=prompt("Digite a senha:");
    }while(senha!=='senha')

    window.sessionStorage.setItem("senha",true);
}

if (window.sessionStorage.getItem("senha") != "true"){
    pedirSenha();
}

function excluir(card){

    $.post( "/postmethod", {
        javascript_data: card 
    });

}