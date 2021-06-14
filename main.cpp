#include <iostream>
#include <stdlib.h>

using namespace std;

class NO
{
public:
    int item;
    NO *esq;
    NO *dir;
};

class Tree
{
  public: NO *root;

  public: Tree()
  {
      root = NULL;
  }

  public: void inserir(int v)
  {
    NO *novo = new NO();
    novo->item = v;
    novo->dir = NULL;
    novo->esq = NULL;
    if (root == NULL)
        root = novo;
    else
    {
      NO *atual = root;
      NO *anterior;
      while(true)
      {
        anterior = atual;
        if (v <= atual->item)
        {
          atual = atual->esq;
          if (atual == NULL)
          {
            anterior->esq = novo;
            return;
          }
        }
        else
        {
           atual = atual->dir;
           if (atual == NULL)
           {
             anterior->dir = novo;
             return;
           }
        }
      }
    }
  }

  public: NO *buscar(int chave)
  {
    if (root == NULL)
        return NULL;

    NO *atual = root;
    while (atual->item != chave)
    {
      if(chave < atual->item )
        atual = atual->esq;
      else
        atual = atual->dir;
      if (atual == NULL)
        return NULL;
    }
    return atual;
  }


  public: bool remover(int v)
  {
    if (root == NULL)
        return false;
    NO *atual = root;
    NO *pai = root;
    bool filho_esq = true;

    while (atual->item != v)
    {
      pai = atual;
      if(v < atual->item )
      {
        atual = atual->esq;
        filho_esq = true;
      }
      else
      {
        atual = atual->dir;
        filho_esq = false;
      }
      if (atual == NULL)
        return false;
    }

    if (atual->esq == NULL && atual->dir == NULL)
    {
      if (atual == root )
        root = NULL;
      else if (filho_esq)
        pai->esq = NULL;
      else
        pai->dir = NULL;
    }
    else if (atual->dir == NULL)
    {
       if (atual == root)
        root = atual->esq;
       else if (filho_esq)
        pai->esq = atual->esq;
       else
        pai->dir = atual->esq;
    }

    else if (atual->esq == NULL)
    {
       if (atual == root)
        root = atual->dir;
       else if (filho_esq)
        pai->esq = atual->dir;
       else
        pai->dir = atual->dir;
    }

    else
    {
      NO *sucessor = no_sucessor(atual);
      if (atual == root)
        root = sucessor;
      else if(filho_esq)
        pai->esq = sucessor;
      else
        pai->dir = sucessor;

      sucessor->esq = atual->esq;
    }

    return true;
  }

  private: NO *no_sucessor(NO *apaga)
  {
     NO *paidosucessor = apaga;
     NO *sucessor = apaga;
     NO *atual = apaga->dir;

     while (atual != NULL)
     {
       paidosucessor = sucessor;
       sucessor = atual;
       atual = atual->esq;
     }

     if (sucessor != apaga->dir)
     {
       paidosucessor->esq = sucessor->dir;
       sucessor->dir = apaga->dir;
     }
     return sucessor;
  }


  public: void imprimir(NO *atual)
  {
    if (atual != NULL)
    {
      imprimir(atual->esq);
      printf("%d ",atual->item);
      imprimir(atual->dir);
    }
  }

  public: bool vazia()
  {
      if(root == NULL)
        return true;
    return false;
  }

};


main()
{
    Tree arv;
    int cont = 2, numero;

    while(cont > 0)
    {
        scanf("%d",&cont);
        for(int i=0;i<cont;i++)
        {
            scanf("%d", &numero);
            if(!arv.remover(numero))
                arv.inserir(numero);
        }
        arv.imprimir(arv.root);
        printf("\n");
        arv.root = NULL;
    }
}
