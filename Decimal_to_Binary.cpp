#include<iostream>
using namespace std;
struct node 
{
  int value;
  node * next;
};
void add_digit(node *& ,int value);
void print_binary(node *&);
int main()
{
  cout << "Enter a Ddecimal_Value : ";
  long long decimal_value;
  int remainder ;
  cin >> decimal_value;
  node * sptr = NULL;
  while(decimal_value / 2 != 0)
  {
    remainder = decimal_value % 2;
    add_digit(sptr,remainder);
    decimal_value /= 2;
  }
  remainder = decimal_value % 2;
  add_digit(sptr,remainder);
  cout << "The Binary Value Is    : ";
  print_binary(sptr);
}
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
void print_binary(node *& sptr)
{
  int size = 0;
  node * assistant_ptr = sptr;
  while(assistant_ptr!= NULL)
  {
    size++;
    assistant_ptr = assistant_ptr->next;
  }
  assistant_ptr = sptr;
  int binary[size];
  for(int i = 0 ; i < size ; i++)
  {
    binary[i] = assistant_ptr->value;
    assistant_ptr = assistant_ptr->next;
  }
  for (int i = size-1 ; i >=0 ; i--)
  {
    cout << binary[i] << " "; 
  }
}