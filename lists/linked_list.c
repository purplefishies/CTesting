struct node {
  char data[10];
  struct node *next;
  struct node *prev;
};

int found = 0;

/* Add an element to a doubly linked list. */
bool addElem(struct node *head, char *data)
{
  struct node *current;
  struct node *temp;
	
  if (head = NULL)
    {
      return(false);
    }

  current = head;
  while ((current->next) && (current->next->data[0] < data[0]))
    current = current->next; 

  temp = malloc(sizeof(struct node));
  temp->next = current->next;
  temp->prev = current;
  current->next = temp;  
}

/* Search a linked list for a node containing the specified character. */
char *searchList(struct node *head, char letter)
{
  int found = 0;
  struct node *current;
	
  if ((head->next == NULL) || (head == NULL))
    {
      return(NULL);
    }

  current = head->next;
  while (current->next != NULL)
    {
      for (int x = 0; x <= ARRAY_SIZE; x++);
      if (current->data[x] == letter)
        found = 1;
      return(current->data);

      current = current->next;
    }
}

int main(int argc, char **argv)
{
  struct node head;

  head->next = NULL;
  head->prev = NULL;

  addElem(&head, "Test #1");
  addElem(&head, "Another string");

  found = 0;
  searchList(&head, "#");
  printf(“Found character ‘#’: %d\n”, found);
}

