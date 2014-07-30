void add(Bignum *pa, Bignum *pb) {
  for(int i = 0; i < pa->len && i < pb->len; i++) {
    pa->arr[i] += pb->arr[i];
  }
}


void copyBignum(Bignum *dest, Bignum *src) {
  dest->len = src->len;
  for(int i = 0; i < src->len; i++) {
    dest->arr[i] = src->arr[i];
  }
}

Bignum res;
initBignum(&res);

for(int i = 1; i < n; i++) {
  Bignum tmp;
  copyBignum(&tmp, &res);
  mult10(&res);
  add(&res, &tmp);
}


struct Bignum {
  int len;
  int *arr;
};


void initBignum(Bignum *pa) {
  pa->len = 1;
  pa->arr = (int*)malloc(M*sizeof(int));
  pa->arr[0] = 1;
}

void freeBignum(Bignum *pa) {
  free(pa->arr);
}

Bignum res;

initBignum(&res);


void copyBignum(Bignum *dest, Bignum *src) {
  dest->len = src->len;
  for(int i = 0; i < src->len; i++) {
    dest->arr[i] = src->arr[i];
  }
}
for(int i = 1; i < n; i++) {
  Bignum tmp;
  initBignum(tmp);
  copyBignum(&tmp, &res);
  mult10(&res);
  add(&res, &tmp);
  freeBignum(tmp);
}
freeBignum(res);


struct Bignum {
  int len;
  int *arr;
};

void initBignum(Bignum *pa) {
  pa->len = 1;
  pa->arr = (int*)malloc(M*sizeof(int));
  pa->arr[0] = 1;
}

initBignum(a);

Bignum res;
for(int i = 1; i < n; i++) {
  Bignum new_a = mult10(&a);
  res = addBignum(a, new_a);
  freeBignum(new_a);
  freeBignum(a);
  a = res;
}
freeBignum(a);
