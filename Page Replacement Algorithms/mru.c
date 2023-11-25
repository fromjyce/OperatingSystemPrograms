/*Implementation of Most Recently Used Page Replacement Algorithm*/

#include <stdio.h>

#define MAX_PAGES 4

// Function to find the index of the most recently used page
int findMRUPage(int pages[], int n) {
    int mruIndex = n - 1;  // Start with the last page as MRU

    // Traverse the pages in reverse order to find the most recently used page
    for (int i = n - 2; i >= 0; i--) {
        if (pages[i] == pages[n - 1]) {
            mruIndex = i;
            break;
        }
    }

    return mruIndex;
}

// Function to simulate the MRU page replacement algorithm
void mruPageReplacement(int pages[], int n, int pageToBeReplaced) {
    // Check if the page to be replaced is already in memory
    for (int i = 0; i < n; i++) {
        if (pages[i] == pageToBeReplaced) {
            printf("Page %d is already in memory. No page fault.\n", pageToBeReplaced);
            return;
        }
    }

    // If memory is not full, insert the new page at the end
    if (n < MAX_PAGES) {
        pages[n] = pageToBeReplaced;
        printf("Page %d is loaded into memory.\n", pageToBeReplaced);
        return;
    }

    // Replace the most recently used page with the new page
    int mruIndex = findMRUPage(pages, n);
    printf("Page %d is loaded into memory, replacing page %d.\n", pageToBeReplaced, pages[mruIndex]);
    pages[mruIndex] = pageToBeReplaced;
}

int main() {
    int pages[MAX_PAGES] = {1, 2, 3};  // Initial pages in memory
    int numPages = 3;

    // Simulate page requests
    int pageRequests[] = {4, 2, 1, 5, 2, 4, 3, 1};
    int numRequests = sizeof(pageRequests) / sizeof(pageRequests[0]);

    // Process page requests
    for (int i = 0; i < numRequests; i++) {
        mruPageReplacement(pages, numPages, pageRequests[i]);
    }

    return 0;
}
