/*Implementation of Worst Fit*/

#include <stdio.h>
#define max 25
int main() {
int frag[max], b[max], f[max], ff[max];
int i, j, nb, nf, highest = 0;
printf("\n\tMemory Management Scheme - Worst Fit");
printf("\nEnter the number of blocks:");
scanf("%d", &nb);
printf("Enter the number of processes:");
scanf("%d", &nf);
printf("\nEnter the size of the blocks:\n");
for (i = 1; i <= nb; i++) {
printf("Block %d:", i);
scanf("%d", &b[i]);
}
printf("Enter the size of the processes:\n");
for (i = 1; i <= nf; i++) {
printf("Process %d:", i);
scanf("%d", &f[i]);
}
for (i = 1; i <= nf; i++) {
highest = 0;
for (j = 1; j <= nb; j++) {
if (b[j] >= f[i] && ff[j] == 0) {
if (highest < (b[j] - f[i])) {
ff[i] = j;
highest = b[j] - f[i];
}
}
}
frag[i] = highest;
}
printf("\nFile_no:\tProcess_size:\tBlock_no:\tBlock_size:\tFragment");
for (i = 1; i <= nf; i++) {
printf("\n%d\t\t%d\t\t%d\t\t%d\t\t%d", i, f[i], ff[i], b[ff[i]], frag[i]);
}
return 0;
}
