// this is an unfinished work.
#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

bool is_light;

typedef enum {
    color,
    quote,
    position,
    size,
} identifier_type;

typedef struct hash {
    char* id;
    char* value;
    identifier_type type;
} hash;

typedef struct {
    char* svg_dat;
    hash* hash_map;
    size_t hash_length;
} wrapper;

char* hsvToRgb(float h, float s, float v) {
    float red, green, blue;

    if (s == 0.0f) {
        red = green = blue = v;
    } else {
        float f, p, q, t;
        int i;

        h /= 60.0f;
        i = (int)h;
        f = h - i; 
        p = v * (1.0f - s);
        q = v * (1.0f - s * f);
        t = v * (1.0f - s * (1.0f - f));

        switch (i) {
            case 0:
                red = v; green = t; blue = p;
                break;
            case 1:
                red = q; green = v; blue = p;
                break;
            case 2:
                red = p; green = v; blue = t;
                break;
            case 3:
                red = p; green = q; blue = v;
                break;
            case 4:
                red = t; green = p; blue = v;
                break;
            default: 
                red = v; green = p; blue = q;
                break;
        }
    }
    int r = (int)(red * 255);
    int g = (int)(green * 255);
    int b = (int)(blue * 255);

    char* result = (char*)malloc(20);
    if (result != NULL) {
        sprintf(result, "rgb(%d,%d,%d)", r, g, b);
    }
    return result;
}

char* greet() {
    time_t now;
    now = time(NULL);
    struct tm *local = localtime(&now);
    
    int hour = local->tm_hour;

    if (hour >= 5 && hour < 12) {
        return "Good morning!";
    } else if (hour >= 12 && hour < 17) {
        return "Good afternoon!";
    } else if (hour >= 17 && hour < 21) {
        return "Good evening!";
    } else {
        return "Good night!";
    }
    return "oops! something happened!";
}

int get_random_range(int x, int y) {
    srand(time(0));
    if (x > y) {
        int temp = x;
        x = y;
        y = temp;
    }
    return x + rand() % (y - x + 1);
}

char* get_quote() {
    char* quotes[] = {
        "Focus on progress, not perfection.",
        "Small steps every day lead to big results.",
        "Success is the sum of small efforts, repeated daily.",
        "Start where you are. Use what you have. Do what you can.",
        "Discipline is the bridge between goals and accomplishment.",
        "Don’t wish for it. Work for it.",
        "You don’t have to be perfect to be amazing.",
        "Dream big. Start small. Act now.",
        "Your future depends on what you do today.",
        "Push yourself, because no one else is going to do it for you."
    };
    
    int num_quotes = sizeof(quotes) / sizeof(quotes[0]);
    srand(time(0));
    int index = rand() % num_quotes;
    return quotes[index];
}

char test_svg[] = "<?xml version=\"1.0\" encoding=\"utf-8\"?><svg xmlns=\"http://www.w3.org/2000/svg\" viewBox=\"0 0 1920 1080\" preserveAspectRatio=\"xMidYMid slice\"><rect x=\"-0.272\" y=\"-1.493\" width=\"1923.244\" height=\"1081.065\" style=\"fill: $sun_color$;\"/><ellipse style=\"fill: rgb(241, 234, 151);\" cx=\"466.112\" cy=\"269.946\" rx=\"174.149\" ry=\"174.149\"/><text style=\"fill: rgb(51, 51, 51); font-family: Arial, sans-serif; font-size: 48px; white-space: pre;\" x=\"833.25\" y=\"507.897\">$greet_day$</text></svg>";
hash test_maps[] = {
  {"sun_color", "rgb(0, 0, 0)", color},
  {"greet_day", "asdf", quote},
};


void clear_buffer(char* buffer) {
    for (size_t i = 0; buffer[i] != '\0'; i++) {
        buffer[i] = '\0';
    }
}

wrapper wrapper_init(char svg_dat[], hash mappings[], size_t length) {
    return (wrapper) {
        .svg_dat = strdup(svg_dat),
        .hash_map = mappings,
        .hash_length = length,
    };
}

char* num_to_str(int num) {
    char buff[20];
    sprintf(buff, "%d", num);
    return strdup(buff);
}

char* readFileLineByLine(const char* filename) {
    FILE* file = fopen(filename, "r");
    char *lines = malloc(1024);  // Buffer for each line
    if (file == NULL) {
        printf("Error opening file: %s\n", filename);
        return NULL;
    }
    while (fgets(lines, sizeof(lines), file) != NULL) {
        printf("%s", lines);
    }
    fclose(file);
    return lines;
}

char* read_file_content(const char* filename) {
    // Open file
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        return NULL;
    }
    // Get file size
    if (fseek(file, 0, SEEK_END) != 0) {
        fclose(file);
        return NULL;
    }
    long file_size = ftell(file);
    if (file_size == -1) {
        fclose(file);
        return NULL;
    }
    // Return to start of file
    rewind(file);
    // Allocate memory for file content plus null terminator
    char* content = (char*)malloc(file_size + 1);
    if (content == NULL) {
        fclose(file);
        return NULL;
    }
    // Read file content
    size_t read_size = fread(content, 1, file_size, file);
    if (read_size != (size_t)file_size) {
        free(content);
        fclose(file);
        return NULL;
    }
    // Null terminate the string
    content[read_size] = '\0';

    // Clean up
    fclose(file);
    return content;
}

wrapper init_paws() {
    char* svg_dat = read_file_content("./assets/paws_template.svg");
    printf("%s", svg_dat);

    hash map[13] = {
        {"theme", (is_light) ? "rgb(255, 255, 255)" : "rgb(0, 0, 0)", color},
        {"circle_color1", hsvToRgb(get_random_range(0, 360), 0.22, 0.8), color},
        {"circle_color2", hsvToRgb(get_random_range(0, 360), 0.22, 0.8), color},
        {"circle_color3", hsvToRgb(get_random_range(0, 360), 0.22, 0.8), color},
        {"circle_color4", hsvToRgb(get_random_range(0, 360), 0.22, 0.8), color},
        {"circle_color5", hsvToRgb(get_random_range(0, 360), 0.22, 0.8), color},
        {"circle_color6", hsvToRgb(get_random_range(0, 360), 0.22, 0.8), color},
        {"circle_radius1", num_to_str(get_random_range(35, 80)), size},
        {"circle_radius2", num_to_str(get_random_range(35, 80)), size},        
        {"circle_radius3", num_to_str(get_random_range(35, 80)), size},
        {"circle_radius4", num_to_str(get_random_range(35, 80)), size},
        {"circle_radius5", num_to_str(get_random_range(35, 80)), size},
        {"circle_radius6", num_to_str(get_random_range(35, 80)), size},
    };

    return wrapper_init(svg_dat, map, 13);
}

char* replace_identifier(wrapper preset) {
    char *modified_svg = (char*)malloc(strlen(preset.svg_dat) * 2);
    char buffer[30];
    size_t j = 0, k;
    for (int i = 0; preset.svg_dat[i] != '\0'; i++) {
        if (preset.svg_dat[i] != '\\' && preset.svg_dat[i] != '$') {
            modified_svg[j++] = preset.svg_dat[i];
        }
        if (preset.svg_dat[i] == '$') {
            k = 0;
            clear_buffer(buffer);
            i++;
            while (preset.svg_dat[i] != '$') {
             buffer[k++] = preset.svg_dat[i++];
            }

            for (k = 0; k < preset.hash_length; k++) { 
                if (strcmp(buffer, preset.hash_map[k].id) == 0) {
                    for (int l = 0; l < strlen(preset.hash_map[k].value); l++) {
                        modified_svg[j++] = preset.hash_map[k].value[l];
                    }
                }
            }
        }
    }
    return (char*)strdup(modified_svg);
}



int main() {
    wrapper w = init_paws();
    printf("%s\n", replace_identifier(w));
    return 0;
}
