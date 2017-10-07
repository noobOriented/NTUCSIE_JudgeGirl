#include <stdio.h>
#include <stdlib.h>

typedef struct Directory {
    char name[256];
    struct Directory *childDir;
    struct Directory *silbingDir;
} Directory;
 
void print1(int depth, int head, char name[]) {
	for(int i = 0; i < depth; ++i) {
		if(i < head)
			printf("   ");
		else
			printf("|  ");
	}
	printf("+- %s\n", name);
}

void print2(int depth, int head) {
	for(int i = 0; i < depth; ++i) {
		if(i < head)
			printf("   ");
		else
			printf("|  ");
	}
	printf("|\n");
}

void dfs(Directory *fs, int depth, int head) {
	if(fs == NULL)
		return;
	print2(depth, head);
	print1(depth, head, fs->name);
	head += (fs->silbingDir == NULL);
	dfs(fs->childDir, depth + 1, head);
	dfs(fs->silbingDir, depth, head);
}

void tree(Directory *fs) {
	printf("+- %s\n", fs->name);
	dfs(fs->childDir, 1, 1);
}

Directory* cd(Directory *fs, char path[]) {
	char name[256];
	int i;
	while(isalpha(path[i])) {
		name[i] = path[i];
		++i;
	}
	name[i] = '\0';
	Directory *x = fs->childDir;
	while(x != NULL) {
		if(!strcmp(name, x->name)){
			if(path[i] == '\0')
				return x;
			return cd(x, path + i + 1);
		}
		x = x->silbingDir;
	}
	return NULL;
}
