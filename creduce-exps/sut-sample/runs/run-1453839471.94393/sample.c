foo() {
  int *p = malloc(sizeof(int));
  free(p);
  free(p);
}
main() {}
