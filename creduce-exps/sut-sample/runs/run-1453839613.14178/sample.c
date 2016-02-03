foo() {
  int *p = rand();
  free(p);
  free(p);
}
main() {}
