/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   not_needed.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtuomine <mtuomine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/08 20:10:42 by mtuomine          #+#    #+#             */
/*   Updated: 2020/03/15 10:07:50 by mtuomine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Debugging macro. */
#if 1
FILE *lndebug_fp = NULL;
#define lndebug(...) \
    do { \
        if (lndebug_fp == NULL) { \
            lndebug_fp = fopen("/tmp/linedit.txt","a"); \
            fprintf(lndebug_fp, \
            "[%d %d %d]", \
            1,2,3); \
        } \
        fprintf(lndebug_fp, __VA_ARGS__); \
        fflush(lndebug_fp); \
    } while (0)
#else
#define lndebug(fmt, ...)
#endif


void hist_print(t_hist *node)
{
	while (node != NULL)
	{
		ft_printf("[%2d] HIST: [%s]\n", node->i, node->str);
		node = node->next;
	}
}


void *ft_realloc(void *ptr, size_t org_len, size_t new_len)
{
	void *new;

	if (!new_len)
	{
		free(ptr);
		return (NULL);
	}
	else if (!ptr)
	{
		return malloc(new_len);
	}
	else if (new_len <= org_len)
	{
		return (ptr);
	}
	else
	{
		new = malloc(new_len);
		if (new)
		{
			// FT_MEMCPY
			memcpy(new, ptr, org_len);
			free(ptr);
		}
		return (new);
	}
}


/* Use the ESC [6n escape sequence to query the horizontal cursor position
 * and return it. On error -1 is returned, on success the position of the
 * cursor. */
static int getCursorX(int ifd, int ofd) {
    char buf[32];
    int cols, rows;
    unsigned int i = 0;

    /* Report cursor location */
    if (write(ofd, "\x1b[6n", 4) != 4) return -1;

    /* Read the response: ESC [ rows ; cols R */
    while (i < sizeof(buf)-1) {
        if (read(ifd,buf+i,1) != 1) break;
        if (buf[i] == 'R') break;
        i++;
    }
    buf[i] = '\0';

    /* Parse it. */
    if (buf[0] != ESC || buf[1] != '[') return -1;
    if (sscanf(buf+2,"%d;%d",&rows,&cols) != 2) return -1;
    return cols;
}

static void insert_char(int key, t_line *line)
{
	tputs(tgetstr("im", NULL), 1, &print_char);
	tputs(tgetstr("ic", NULL), 1, &print_char);
	// // Put char on screen
	ft_putchar(key);
	tputs(tgetstr("ei", NULL), 1, &print_char);
	// // Put char in buffer
	ft_insert(line->input, line->i + 1, (char)key);
	line->i++;
	line->len++;
	line->cursor.x++;
}

static void reset_input(t_line *line)
{
	ft_bzero(line->input, INPUT_BUFFER);
	line->pos = 0;
	line->lines_used = 1;
	line->offset = 0;
	line->len = 0;
}
