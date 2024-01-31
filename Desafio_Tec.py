import csv

lista_filmes = []

class Filmes:
    def __init__(self,nome,avaliacao,nota):
        self.nome = nome
        self.avaliacao = avaliacao
        self.nota = nota
    
    def carregar_dados(self):  #Carrega os dados salvos e transforma em atrivutos do objeto
        dados = open('filmes.csv')
        leitor = csv.reader(dados)
        array =list(leitor)
        for i in range(len(array)):
            self.nome = array[i][0]
            self.avaliacao = array[i][1]
            self.nota = array[i][2]
            lista_filmes.append(self)
        dados.close()
        
    
    def dar_nota(self):
        nota = int(input('Informe uma nota de 1 a 5 para o filme: '))
        v = 0
        while v==0:
            if nota > 0 and nota <=5:
                v+=1
            else:
                print("nota inválida. Digite um valor entre 1 e 5")
                nota = int(input('Informe uma nota de 1 a 5 para o filme'))
        else:
            self.nota = nota
            print('nota adicionada com sucesso!')
    
    def avaliar(self):
        avaliacao = input('Escreva aqui sua crítica/avaliação sobre o filme: ')
        self.avaliacao = avaliacao

    
def menu():
    print("[1] - Adicionar filme \n [2] - Deletar filme da lista \n [3] - Avaliar filme \n [4] - Mostrar lista de filmes \n [5] - Encerrar programa")
    escolha = int(input('informe a opção desejada:'))
    return escolha

filme = Filmes('','','')
filme.carregar_dados()
escolha = menu()


while escolha != 5:

    if escolha == 1:
        nome_filme = input('informe o nome do filme que você deseja adicionar à lista: ')
        filme = Filmes(nome_filme,'não avaliado','sem nota')
        escolha_avaliacao = int(input('Você deseja deixar uma avaliação sobre o filme? [1] - Sim [2] - Não\nDigite sua escolha: '))
        if escolha_avaliacao == 1:
            filme.dar_nota()
            filme.avaliar()
        lista_filmes.append(filme)
        print('Filme adicionado com sucesso!')

    elif escolha == 2:
        nome_filme = input("informe o nome do filme que você deseja excluir da lista: ")
        for i in range(len(lista_filmes)):
            if lista_filmes[i].nome == nome_filme:
                print('O filme {} foi exluído com sucesso!'.format(lista_filmes[i].nome))
                lista_filmes.pop(i)

    elif escolha == 3:
        nome_filme = input('Informe o nome do filme que você gostaria de avaliar: ')
        for i in range(len(lista_filmes)):
            if lista_filmes[i].nome == nome_filme:
               lista_filmes[i].dar_nota()
               lista_filmes[i].avaliar()
        for i in range(len(lista_filmes)):
            if lista_filmes[i].avaliacao == 'não avaliado':
                print('[',lista_filmes[i].nome,' ainda não foi avaliado por você]')

    elif escolha == 4:
        for i in range(len(lista_filmes)):
            print('[NOME] - ',lista_filmes[i].nome,'\n[AVALIAÇÃO] - ',lista_filmes[i].avaliacao,'\n[NOTA] - ',lista_filmes[i].nota)
            print('')

    else:
        print('valor inválido, favor digitar uma nova opção')
    escolha = menu()

else:
    dados = open('filmes.csv','w')
    writer = csv.writer(dados)
    for i in range(len(lista_filmes)):
        writer.writerow([lista_filmes[0].nome,lista_filmes[0].avaliacao,lista_filmes[0].nota])
        lista_filmes.pop(0)
        break
    dados.close()

    dados_atualizados = open('filmes.csv','a')
    writer = csv.writer(dados_atualizados)
    for i in range(len(lista_filmes)):
        writer.writerow([lista_filmes[i].nome,lista_filmes[i].avaliacao,lista_filmes[i].nota])
    dados_atualizados.close()
    print('Programa encerrado.')
