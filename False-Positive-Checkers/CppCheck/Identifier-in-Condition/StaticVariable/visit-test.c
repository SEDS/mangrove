int main()
{
 static int a = 1;
 int *b = 0;
 if(a < 5)
 {
   b = &a;
   a++;
 }
 *b++;
 return 0;
}
