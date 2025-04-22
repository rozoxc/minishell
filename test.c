#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <string.h>
#include <errno.h>

#define SUCCESS 0
#define FAILURE 1

// Simulated environment structure
typedef struct s_env {
    char *key;
    char *value;
    struct s_env *next;
} t_env;

t_env *g_env = NULL;

// Helper function to update environment variables
void update_env_var(const char *key, const char *value) {
    t_env *env = g_env;
    
    // Search for existing variable
    while (env) {
        if (strcmp(env->key, key) == 0) {
            free(env->value);
            env->value = strdup(value);
            return;
        }
        env = env->next;
    }
    
    // Add new variable if not found
    t_env *new_env = malloc(sizeof(t_env));
    new_env->key = strdup(key);
    new_env->value = strdup(value);
    new_env->next = g_env;
    g_env = new_env;
}

// CD function implementation
int ft_cd(char **args) {
    char old_pwd[PATH_MAX];
    char new_pwd[PATH_MAX];
    char *target_dir = args[1];

    // 1. Handle no argument case (cd $HOME)
    if (!target_dir) {
        target_dir = getenv("HOME");
        if (!target_dir) {
            fprintf(stderr, "cd: HOME not set\n");
            return FAILURE;
        }
    }
    // Handle cd - (switch to OLDPWD)
    else if (strcmp(target_dir, "-") == 0) {
        target_dir = getenv("OLDPWD");
        if (!target_dir) {
            fprintf(stderr, "cd: OLDPWD not set\n");
            return FAILURE;
        }
        printf("%s\n", target_dir);  // Print directory when using cd -
    }

    // 2. Get current directory before changing
    if (getcwd(old_pwd, sizeof(old_pwd)) == NULL) {
        perror("cd: getcwd");
        return FAILURE;
    }

    // 3. Attempt to change directory
    if (chdir(target_dir) != 0) {
        fprintf(stderr, "cd: %s: %s\n", target_dir, strerror(errno));
        return FAILURE;
    }

    // 4. Get new directory after changing
    if (getcwd(new_pwd, sizeof(new_pwd)) == NULL) {
        perror("cd: getcwd");
        return FAILURE;
    }

    // 5. Update environment variables
    update_env_var("OLDPWD", old_pwd);
    update_env_var("PWD", new_pwd);

    return SUCCESS;
}

// Test main function
int main(int argc, char **argv) {
    // Initialize environment with basic variables
    update_env_var("HOME", getenv("HOME"));
    update_env_var("PWD", getenv("PWD"));
    
    // Test cases
    printf("=== Testing cd ===\n");
    
    // 1. Test cd to a valid directory
    printf("\nTest 1: cd to /tmp\n");
    char *test1[] = {"cd", "/tmp", NULL};
    ft_cd(test1);
    printf("Current directory: %s\n", getcwd(NULL, 0));
    
    // 2. Test cd with no arguments (should go to HOME)
    printf("\nTest 2: cd (no argument)\n");
    char *test2[] = {"cd", NULL};
    ft_cd(test2);
    printf("Current directory: %s\n", getcwd(NULL, 0));
    
    // 3. Test cd - (should return to previous directory)
    printf("\nTest 3: cd -\n");
    char *test3[] = {"cd", "-", NULL};
    ft_cd(test3);
    printf("Current directory: %s\n", getcwd(NULL, 0));
    
    // 4. Test cd to invalid directory
    printf("\nTest 4: cd to invalid directory\n");
    char *test4[] = {"cd", "/nonexistent_directory", NULL};
    ft_cd(test4);
    
    return 0;
}