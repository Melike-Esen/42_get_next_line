# Get_Next_Line

`get_next_line` (GNL), bir dosya tanıtıcısından (file descriptor) satır satır okuma yapan bir C fonksiyonudur. Her çağrıldığında bir sonraki satırı döndürür ve dosyanın sonuna gelindiğinde `NULL` döner.

---

## Özellikler
- Satırları dinamik olarak okur, satır uzunluğu sınırsızdır.
- `BUFFER_SIZE` makrosu ile okuma boyutu özelleştirilebilir.
- Memory leak-free, tüm malloc edilen bellekler yönetiliyor.
- `\n` karakterini de satırın içinde döndürür.

---

## Kullanım

```c
#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int fd = open("test.txt", O_RDONLY);
    if (fd < 0)
        return (1);

    char *line;
    while ((line = get_next_line(fd)) != NULL)
    {
        printf("%s", line);
        free(line); // her satırdan sonra free edilmeli
    }

    close(fd);
    return (0);
}
