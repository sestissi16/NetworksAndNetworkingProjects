#include<stdio.h>
#include<stdlib.h>
//Sari Stissi
//Assigment 2
//Collaborated with Ethan Rountree, Laurence, Sara, and Jordan on this homework

struct student{
  char *fname;
  char *lname;
  int age;
  char *dob;
};

struct studentNode{
  struct student *data;
  struct studentNode *nextStudent;
};

struct singlyLinkedList{
  struct studentNode *head;
  struct studentNode *tail;
};


typedef struct student *student;
typedef struct studentNode *node;
typedef struct singlyLinkedList *linkedList;

student createStudent(char *fname, char *lname, int age, char *dob){
  student temp;
  temp = (student)malloc(sizeof(struct student));
  temp->fname = fname;
  temp->lname = lname;
  temp->age = age;
  temp->dob = dob;
  return temp;
}

node createNode(student studentData){
  node temp;
  temp = (node)malloc(sizeof(struct studentNode));
  temp->data = studentData;
  temp->nextStudent = NULL;
  return temp;
}

linkedList createList(){
  linkedList temp;
  temp = (linkedList)malloc(sizeof(struct singlyLinkedList));
  temp->head = NULL;
  temp->tail = NULL; 
  return temp;
}

void add_head(linkedList LinkedList, student studentToAdd){
  node newNode = createNode(studentToAdd);
  if(LinkedList->head == NULL){
    LinkedList->head = newNode;
    LinkedList->tail = newNode;
  }
  else{
    newNode->nextStudent = LinkedList->head;
    LinkedList->head = newNode;
  }
}

void add_tail(linkedList LinkedList, student studentToAdd){
  node newNode = createNode(studentToAdd);
  if(LinkedList->tail == NULL){
    LinkedList->head = newNode;
    LinkedList->tail = newNode;
  }
  else{
    LinkedList->tail->nextStudent = newNode;
    LinkedList->tail = newNode;
  }
}

void add_after(linkedList LinkedList, student findStudent, student studentToAdd){
  node addAfter = createNode(findStudent);
  node newNode = createNode(studentToAdd);
  node currentNode = LinkedList->head;
  node nextNode = LinkedList->head->nextStudent;
  if(LinkedList->head == NULL && LinkedList->tail == NULL){
    printf("%s\n", "Error: please add a head or a tail first");
  }
  while(currentNode->data != addAfter->data){
    currentNode = nextNode;
    nextNode = currentNode->nextStudent;
    if(currentNode->nextStudent == NULL && currentNode->data != addAfter->data){
      printf("%s\n", "Error: node not found");
      break;
    }
  }
  if(currentNode->nextStudent == NULL){
    add_tail(LinkedList, newNode->data);
  }
  else{
    currentNode->nextStudent = newNode;
    newNode->nextStudent = nextNode;
  }
}

int searchStudents(linkedList LinkedList, student findStudent){
  node findStudentNode = createNode(findStudent);
  node currentNode = LinkedList->head;
  while(currentNode->data != findStudentNode->data){
    currentNode = currentNode->nextStudent;
    if(currentNode->nextStudent == NULL && currentNode->data != findStudentNode->data){
      printf("%s\n", "Error: The student you're looking for was not found.");
      return 0;
    }
  }
  printf("%s\n", "The student is in the list!");
  return 1;
}

void removeStudent(linkedList LinkedList, student studentToRemove){
  node nodeToRemove = createNode(studentToRemove);
  node currentNode = LinkedList->head;
  node prevNode = NULL;
  if(LinkedList->head == NULL && LinkedList->tail == NULL){
    printf("%s\n", "Error: There are no nodes to remove");
  }
  else{
    while(currentNode->data != nodeToRemove->data){
      prevNode = currentNode;
      currentNode = currentNode->nextStudent;
      if(currentNode->nextStudent == NULL && currentNode->data != nodeToRemove->data){
        printf("%s\n", "Error: The Student you were looking to remove was not found");
        break;
      }
    }
    if(prevNode == NULL){
      if(currentNode->nextStudent == NULL){
        LinkedList->head = NULL;
        LinkedList->tail = NULL;
      }
      else{
        LinkedList->head = currentNode->nextStudent;
        currentNode->nextStudent = NULL;
      }
    }
    else if(currentNode->nextStudent == NULL){
      prevNode->nextStudent = NULL;
      LinkedList->tail = prevNode;
    }
    else{
      prevNode->nextStudent = currentNode->nextStudent;
      currentNode->nextStudent  = NULL;
    }
  }
}

void printIndivStudent(student StudentToPrint){
  printf("First Name: %s, Last Name: %s, Age: %d, Date of Birth: %s\n",
  StudentToPrint->fname,
  StudentToPrint->lname,
  StudentToPrint->age,
  StudentToPrint->dob);
}

void printList(linkedList LinkedList){
  node currentNode = LinkedList->head;
  printf("%s:\n", "List of Students");
  if(LinkedList->head == NULL && LinkedList->tail == NULL){
    printf("%s\n", "There are no Students in this list.");
  }
  else{
    while(currentNode->nextStudent != NULL){
      student StudentToPrint = currentNode->data;
      printIndivStudent(StudentToPrint);
      currentNode = currentNode->nextStudent;
    }
    printIndivStudent(LinkedList->tail->data);
  }
}

void main(){
  student Student1 = createStudent("Sari", "Stissi", 20, "02/27/1998");
  student Student2 = createStudent("Sara", "Salloum", 21, "03/24/1997");
  student Student3 = createStudent("Bob", "Billy", 35, "06/23/1976");
  student Student4 = createStudent("Jessica", "Star", 65, "10/05/1959");
  student Student5 = createStudent("Bitch Boy", "Cluster Fuck", 69, "06/06/6666");
  linkedList FirstList = createList();
  add_head(FirstList, Student1);
  add_head(FirstList, Student3);
  add_tail(FirstList, Student2);
  add_after(FirstList, Student1, Student4);
  searchStudents(FirstList, Student3);
  searchStudents(FirstList, Student5);
  add_after(FirstList, Student2, Student5);
  searchStudents(FirstList, Student5);
  removeStudent(FirstList, Student5);
  searchStudents(FirstList, Student5);
  printList(FirstList);
}
