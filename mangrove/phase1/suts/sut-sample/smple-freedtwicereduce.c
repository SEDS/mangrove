int somenumber() {
   int z=rand();
   return z;
}
int main(int argc, char** argv) {
   int * p = (int *)malloc(10 * sizeof(int));
   int z=somenumber();
   if ((z % 10) >= 11){ free(p); }
   free(p);
   0;
   return 0;
}