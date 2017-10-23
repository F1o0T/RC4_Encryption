#include <iostream>
#include<math.h>
using namespace std;
void encryption_Algorithm(int plain_text [] , int ,  int initial_key [] , int);
struct node 
{
  int value;
  node * next;
};
void add_digit(node *& ,int );
void get_binary(node *& ,int []);
int  number_of_digits(node *&);
int main()
{
    int plain_text [] = {1,2,2,2};
    int plain_text_size = sizeof(plain_text)/4;
    int initial_key[] = {1,2,3,6,1,2,3,6};
    int initial_key_size = sizeof(initial_key)/4;
    encryption_Algorithm(plain_text, plain_text_size, initial_key, initial_key_size);
}
void encryption_Algorithm(int plain_text [] , int plain_text_size , int initial_key [] , int initial_key_size)
{
    cout << "=================================================================" << endl;
    cout << "Calculating The T[ ]" << endl;
    int T[initial_key_size];
    for(int i = 0 ; i < initial_key_size ; i++)
    {
      int temp = i % initial_key_size;
      T[i] = initial_key[temp];
    }
    ///////////////////////////////////////////////////////
    cout << "T[ ] = [ ";
    for(int i = 0 ; i < initial_key_size ; i++)
    {
      cout << T[i];
      if(i < initial_key_size -1)
        {
          cout << " ,";
        }
    }
    cout << " ]"<<endl<<endl;
    int S[initial_key_size];
    cout << "As we have 8 Byte key, so the initial S[ ]"<<endl;
    cout << "S[ ] = [ ";
    for(int i = 0 ; i < initial_key_size ; i++)
    {
      S[i] = i;
      cout << S[i];
      if(i < initial_key_size -1)
        {
          cout << " ,";
        }
    }
    cout << " ]"<<endl;
    ////////////////////////////////////////////////////////////
    cout << "================================================================="<< endl;
    cout << "Calculating The KSA Output" <<endl;
    int j = 0;
    for(int i = 0 ; i < initial_key_size ; i++)
    {
      j = (j + S[i] + T[i]) % initial_key_size;
      cout<<"Here (i = "<< i << " And J = " << j << ")    >>    S[ ] =  ";
      int temp = S[i];
      S[i] = S[j];
      S[j] = temp;
      for(int i = 0 ; i < initial_key_size ; i++)
      {
        cout <<S[i]<<"  ";
      }
      cout <<endl;
    }
    cout <<endl;
    cout << "The Output of KSA Algorithm is "<< endl << "S[ ] = [ ";
    for(int i = 0 ; i < initial_key_size ; i++)
    {
      cout << S[i];
      if(i < initial_key_size -1)
        {
          cout << " ,";
        }
    }
    cout << " ]"<<endl;
    ////////////////////////////////////////////////////////////////
    cout << "=================================================================" << endl;
    cout << "Calculating The PRGA Output by Taking KSA output as an Input"<<endl;
    int real_key[plain_text_size];
    for(int i = 0 , j = 0 , index =0 ; index < plain_text_size ; index++)
    {
      i = 1 + ((i+  1 ) % initial_key_size);
      j = 1 + ((j+S[i-1]) % initial_key_size); //1 + (1+2)
      cout<<"Here (i = "<< i << " And J = " << j << ")    >>    S[ ] =  ";
      int temp = S[i - 1];
      S[i -1]  = S[j - 1];
      S[j -1]  = temp;
      for(int i = 0 ; i < initial_key_size ; i++)
      {
        cout <<S[i]<<"  ";
      }
      int Ks = 1 + ((S[i-1] + S[j-1]) % initial_key_size);
      cout <<"KS : " << Ks << "  ";
      real_key[index] = S[Ks-1];
      cout <<"real_key[ index ] = " << real_key[index];
      cout <<endl;
    }
    ///////////////////////////////////////////////////////////////////
    cout << "=================================================================" << endl;
    cout << "Converting to Binary . . . And Xoring  . . . And Converting back to Decimal" << endl;
    for (int i = 0 ; i < plain_text_size ; i++)
    {
      int remainder;
      node * sptr = NULL;
      int decimal_value = real_key[i];
      while((decimal_value/ 2) != 0)
      {
        remainder = decimal_value % 2;
        add_digit(sptr,remainder);
        decimal_value /= 2;
      }
      remainder = decimal_value % 2;
      add_digit(sptr,remainder);
      int size = number_of_digits(sptr);
      if(size < 3)
      {
        if (size == 2)
        {
          add_digit(sptr,0);
          size = 3;
        }
        if (size == 1)
        {
          add_digit(sptr,0);
          add_digit(sptr,0);
          size = 3;
        }
      }
      int real_key_binary [size];
      get_binary(sptr, real_key_binary);
      for(int i = 0 ; i < size ; i++)
      {
        cout <<real_key_binary[i] << " ";
      }
      cout <<"   ";
      //--------------------------------------------------------------------------//
      sptr = NULL;
      decimal_value = plain_text[i];
      while((decimal_value/ 2) != 0)
      {
        remainder = decimal_value % 2;
        add_digit(sptr,remainder);
        decimal_value /= 2;
      }
      remainder = decimal_value % 2;
      add_digit(sptr,remainder);
      size = number_of_digits(sptr);
      if(size < 3)
      {
        if (size == 2)
        {
          add_digit(sptr,0);
          size = 3;
        }
        if (size == 1)
        {
          add_digit(sptr,0);
          add_digit(sptr,0);
          size = 3;
        }
      }
      int plain_text_binary [size];
      get_binary(sptr, plain_text_binary);
      for(int i = 0 ; i < size ; i++)
      {
        cout <<plain_text_binary[i] << " ";
      }
      cout <<"   ";
      sptr = NULL;
      int xored [size];
      for(int i = 0 ; i <size ; i++)
      {
        if(plain_text_binary[i] == real_key_binary [i])
        {
            cout << "k = " << real_key_binary [i] << " p = "<<  plain_text_binary[i] <<"  ";
            add_digit(sptr,0);
        }
        else
        {
            cout << "k = " << real_key_binary[i] << " p = "<<  plain_text_binary [i] << "  ";
            add_digit(sptr,1);
        }
      }
      get_binary(sptr,xored);
      int xored_output [size];
      for(int i = 0 , j = size -1 ; i < size ; i++ , j--)
      {
        xored_output[i] = xored[j];
        cout << xored_output[i];
      }
      int sum = 0;
      for(int i = 0 ; i < size ; i++)
      {
        sum += xored[i] * pow(2,i);
      }
      cout << "    In decimal = " << sum;
      cout <<endl;
    }
} 
///////////////////////////////////////////////////////////////////////
void add_digit(node *& sptr,int data)
{
  node * temp  = new node;
  temp->value  = data;
  temp->next   = NULL;
  if(sptr == NULL)
  {
    sptr = temp;
  }
  else
  {
    node * assistant_ptr = sptr;
    while(assistant_ptr -> next != NULL)
    {
      assistant_ptr = assistant_ptr->next;
    }
    assistant_ptr->next=temp;
  }
}
///////////////////////////////////////////////////////////////////////
void get_binary(node *& sptr, int binary [])
{
  int size = 0;
  node * assistant_ptr = sptr;
  while(assistant_ptr!= NULL)
  {
    size++;
    assistant_ptr = assistant_ptr->next;
  }
  assistant_ptr = sptr;
  int moderator [size];
  for(int i = 0 ; i < size ; i++)
  {
    moderator[i] = assistant_ptr->value;
    assistant_ptr = assistant_ptr->next;
  }
  for (int i = 0 , j = size-1 ; i < size ; i++ , j--)
  {
    binary[i] = moderator[j];
  }
}
//////////////////////////////////////////////////////////////////////////
int  number_of_digits(node *& sptr)
{
  int size = 0;
  node * assistant_ptr = sptr;
  while(assistant_ptr!= NULL)
  {
    size++;
    assistant_ptr = assistant_ptr->next;
  }
  return size;
}
