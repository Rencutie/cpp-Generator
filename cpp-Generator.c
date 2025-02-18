#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024

// Extract the class name and return 1 if in a class, 0 else
int extract_class_name(const char *line, char *class_name) {
    if (strstr(line, "class") != NULL && strchr(line, '{') != NULL) {
        char temp[BUFFER_SIZE];
        strcpy(temp, line);
        char *token = strtok(temp, " \t");
        while(token != NULL) {
            if(strcmp(token, "class") == 0) {
                token = strtok(NULL, " \t{");
                if(token != NULL) {
                    strcpy(class_name, token);
                    return 1; // Class found
                }
            }
            token = strtok(NULL, " \t");
        }
    }
    return 0; // Not found
}

// Check if end of class
int is_end_of_class(const char *line) {
    return (strstr(line, "};") != NULL);
}




// Extract info on a methode : return type, methode name and parameters
int extract_method_info(const char *line, char *return_type, char *method_name, char *params) {
    if(strchr(line, '(') && strchr(line, ')') && strchr(line, ';')) {
        char temp[BUFFER_SIZE];
        strcpy(temp, line);
        
        // Remove semicolon 
        char *semicolon = strchr(temp, ';');
        if(semicolon) {
            *semicolon = '\0';
        }
        
        // Find opening parentese to isolate parameters
        char *paren = strchr(temp, '(');
        if(!paren)
            return 0;
        strcpy(params, paren);  
        
        // Terminer la chaîne pour obtenir la partie "type de retour et nom de la méthode"
        *paren = '\0';
        
        // looking for return type 
        char *last_space = strrchr(temp, ' ');
        if(last_space) {
            strcpy(method_name, last_space + 1);
            *last_space = '\0'; // Isolate return type 
            while(*temp == ' ') // Remove indent
                memmove(temp, temp+1, strlen(temp)+1);
            strcpy(return_type, temp);
            return 1;
        } else {
            return 0;
        }
    }
    return 0;
}

// Check the file line by line and write to the cpp file
void process_file(FILE *fin, FILE *fout) {
    char line[BUFFER_SIZE];
    char current_class[256] = "";
    int inside_class = 0;
    
    while(fgets(line, BUFFER_SIZE, fin)) {
        // Remove carriage return
        line[strcspn(line, "\n")] = '\0';
        if(strlen(line) == 0)
            continue;
        
        char class_name[256];
        if(extract_class_name(line, class_name)) {
            strcpy(current_class, class_name);
            inside_class = 1;
            continue;
        }
        
        if(inside_class && is_end_of_class(line)) {
            inside_class = 0;
            current_class[0] = '\0';
            continue;
        }
        
        if(inside_class) {
            char return_type[256];
            char method_name[256];
            char params[BUFFER_SIZE];
            if(extract_method_info(line, return_type, method_name, params)) {
                fprintf(fout, "%s %s::%s%s {\n", return_type, current_class, method_name, params);
                fprintf(fout, "    // TODO\n");
                fprintf(fout, "}\n\n");
            }
            continue;
        }
        if(!inside_class){ // For regular functions
            char return_type[256];
            char function_name[256];
            char params[BUFFER_SIZE];
            if(extract_method_info(line, return_type, function_name, params)){
                fprintf(fout, "%s %s%s {\n", return_type, function_name, params);
                fprintf(fout, "    // TODO\n");
                fprintf(fout, "}\n\n");

            }


        }
    }
}

int main(int argc, char *argv[]) {
    if(argc < 3) {
        fprintf(stderr, "Usage: %s <file.hpp> <file.cpp>\n\nThe file.cpp is created if not found\n", argv[0]);
        return 1;
    }
    
    FILE *fin = fopen(argv[1], "r");
    if(!fin) {
        perror("Failed to open input file");
        return 1;
    }
    
    FILE *fout = fopen(argv[2], "w");
    if(!fout) {
        perror("Failed to open/create output file");
        fclose(fin);
        return 1;
    }
    fprintf(fout, "#include \"%s\"\n\n", argv[1]);
    process_file(fin, fout);
    
    fclose(fin);
    fclose(fout);
    
    printf("Succefully generated %s\n", argv[2]);
    return 0;
}
