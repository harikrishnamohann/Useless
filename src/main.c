// welcome to c programing
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


typedef enum {
    color,
    quote,
    position,
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

const char* get_quote() {
    const char* quotes[] = {
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

char* replace_identifier(wrapper preset) {
    char *svg = preset.svg_dat, modified_svg[strlen(svg)], buffer[20];
    size_t j = 0, k;
    for (int i = 0; svg[i] != '\0'; i++) {
        if (svg[i] != '\\' && svg[i] != '$') {
            modified_svg[j++] = svg[i];
        }
        if (svg[i] == '$') {
            i++;
            clear_buffer(buffer);
            k = 0;
            while (svg[i] != '$') {
                buffer[k++] = svg[i++];
            }
            for (k = 0; k < preset.hash_length; k++) { // limit of k should be decided.
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
    wrapper test = wrapper_init(test_svg, test_maps, 2);
    printf("%s\n", replace_identifier(test));
    return 0;
}
