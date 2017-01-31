int a = 1;
int main()
{
 
 int *b = 0;
 if(a < 5)
 {
   b = &a;
   a++;
 }
 *b++;
 return 0;
}
