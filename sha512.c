#include <glib.h>
#include <string.h>
#include <stdio.h>

// gcc -o sha512 sha512 `pkg-config --cflags --libs glib-2.0`
// https://developer.gnome.org/glib/stable/glib-Base64-Encoding.html
  int main(void) {
  char   string[sizeof("Message0000000000")] ="";
  // Digest::SHA512.base64digest("Message0000000000")
  // => "iSwXg5a3uAZ/PW3SGTQbE7B4b0gNv6Cbsc/nZSXf4P2MVOKlmdJgh1PZXDX1UsIMXO5hqfkqK3Fv0b2l5iApVA=="

  gchar  *sha512;
  guchar *sha512_bytes = NULL;
  int shalen;

  for(int ii=0;;ii++) {
    sprintf(string, "Message%010d", ii);
    sha512 = g_compute_checksum_for_string(G_CHECKSUM_SHA512, string, strlen(string));
    if(!sha512_bytes) {
      sha512_bytes = (guchar*) g_malloc(strlen(sha512)/2);
      shalen = strlen(sha512)/2;
    }
    //g_print("%s\n", sha512);
    for(int byte=0; byte < shalen; byte++) {
      char a = sha512[byte*2];
      char b = sha512[byte*2+1];
      a = (a <= '9') ? a - '0' : (a & 0x7) + 9;
      b = (b <= '9') ? b - '0' : (b & 0x7) + 9;
      sha512_bytes[byte] = (a << 4) + b;
    }
    gchar *base64 = g_base64_encode(sha512_bytes, shalen);
    //g_print("%s\n", base64);
    if(strncmp(base64, "TEST", 4) == 0)
    {
      printf("%d %s %s\n", ii, string, base64);
      exit(0);
    }
    //g_print("%s\n", base64);
    g_free(base64);
    g_free(sha512);
  }
  g_free(sha512_bytes);
  return 0;
}
