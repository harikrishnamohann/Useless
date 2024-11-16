
// this program is unfinished.
// it may have critical bugs and it is poorly disigned 
// since it is created in a rush for a hackathon program.

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../include/list.h"
#include "../include/arena.h"

Arena* arena;

typedef struct hash {
    char* id;
    char* value;
} hash;

typedef struct {
    char* svg_dat;
    List hash_map;
    size_t hash_length;
} wrapper;

char* hsvToRgb(float h, float s, float v);
char* greet(); // returns greeting message based on time of the day.
int get_random_range(int x, int y);
char* get_quote(); // returns random motivational quotes
void clear_buffer(char* buffer, size_t size);
char* num_to_str(int num);
char* read_file_content(const char* filename);
static char* join_int_str(char* str, int num);
int write_to_file(const char* filename, const char* data, size_t length);

wrapper wrapper_init(char svg_dat[], List* mappings, size_t length) {
    return (wrapper) {
        .svg_dat = strdup(svg_dat),
        .hash_map = *mappings,
        .hash_length = length,
    };
}

hash* hash_init(char* id, char* value) {
    hash* map = arena_alloc(arena, sizeof(hash));
    map->id = id;
    map->value = value;
    return map;
}

// preset for current svg image
wrapper init_paws() {
    char* svg_dat = read_file_content("./assets/paws_template.svg");
    size_t no_of_entries = 14;
    List mappings = list_init(sizeof(hash) * no_of_entries, sizeof(hash));
    list_insert_at_rear(&mappings, hash_init( "theme", "rgb(238,238,238)"));
    list_insert_at_rear(&mappings, hash_init("greeting", get_quote()));

    for (int i = 1; i < 7; i++) {
        list_insert_at_rear(&mappings, hash_init(join_int_str("circle_color", i),hsvToRgb(get_random_range(0, 300), 0.2f, 0.8f)));
    }

    for (int j = 1, i = 7; i < 13; i++) {
        list_insert_at_rear(&mappings, hash_init(join_int_str("circle_radius", j++) ,num_to_str(get_random_range(35, 80))));
    }
    
    return wrapper_init(svg_dat, &mappings, no_of_entries);
}

char* replace_identifiers(wrapper preset) {
    char *modified_svg = (char*)malloc(strlen(preset.svg_dat) * 2);
    char buffer[30];
    size_t j = 0, k;
    for (int i = 0; preset.svg_dat[i] != '\0'; i++) {
        if (preset.svg_dat[i] != '\\' && preset.svg_dat[i] != '$') {
            modified_svg[j++] = preset.svg_dat[i];
        }
        if (preset.svg_dat[i] == '$') {
            k = 0;
            clear_buffer(buffer, 30);
            i++;
            while (preset.svg_dat[i] != '$') {
             buffer[k++] = preset.svg_dat[i++];
            }

            for (k = 0; k < preset.hash_length; k++) { 
                hash tmp = *(hash*)list_peekat(&preset.hash_map, k);
                if (strcmp(buffer, tmp.id) == 0) {
                    for (int l = 0; l < strlen(tmp.value); l++) {
                        modified_svg[j++] = tmp.value[l];
                    }
                }
            }
        }
    }
    return (char*)strdup(modified_svg);
}


int main() {
    srand(time(NULL));
    arena = arena_init(ARENA_256);

    wrapper w = init_paws();
    char* svg = replace_identifiers(w);

    const char output_file[] = "out.svg";
    write_to_file(output_file, svg, strlen(svg));

    list_free(&w.hash_map);
    arena_free(arena);
    return 0;
}

int write_to_file(const char* filename, const char* data, size_t length) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        return -1;    
    }
    
    size_t written = fwrite(data, 1, length, file);
    fclose(file);
    
    return (written == length) ? 0 : -1;   
}

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

char* read_file_content(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        return NULL;
    }
    if (fseek(file, 0, SEEK_END) != 0) {
        fclose(file);
        return NULL;
    }
    long file_size = ftell(file);
    if (file_size == -1) {
        fclose(file);
        return NULL;
    }
    rewind(file);
    char* content = (char*)malloc(file_size + 1);
    if (content == NULL) {
        fclose(file);
        return NULL;
    }
    size_t read_size = fread(content, 1, file_size, file);
    if (read_size != (size_t)file_size) {
        free(content);
        fclose(file);
        return NULL;
    }
    content[read_size] = '\0';

    fclose(file);
    return content;
}

void clear_buffer(char* buffer, size_t size) {
    for (size_t i = 0; i < size; i++) {
        buffer[i] = '\0';
    }
}
char* num_to_str(int num) {
    char buff[20];
    sprintf(buff, "%d", num);
    return strdup(buff);
}

static char* join_int_str(char* str, int num) {
    char *buffer = arena_alloc(arena, strlen(str) + 2);
    sprintf(buffer, "%s%d", str, num);
    return buffer;
}
