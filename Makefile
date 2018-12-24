CC=gcc
CFLAGS=-Wall -g -Wno-pointer-sign

BIN = UnionDec libmyso.so
LIBLD= -L../../lib64 -L/usr/lib64/mysql/ -L/usr/lib64/ -luniondb_s \
	-luniondb_s -lunionxml_s -lunionencrypt_s -lmysqlclient -lxml2 \
	-lunionlog_s -lclntsh -lunionbox_s  -lunionlic_s -lunioncodec_s \
	-luniongettext_s -lunioncommcli_s -lunionsock_s -lunionsso_s -lmyso

#TEST=soexe

.PHONY: all
all: $(BIN) 
libmyso.so:common.c
	$(CC) $(CFLAGS) -shared -fPIC -o $@ $^ 
	cp libmyso.so /usr/lib64/

UnionDec: main.c
	$(CC) $(CFLAGS) -o $@ $^ $(LIBLD)

#test: $(TEST)
#soexe: main.c
#	$(CC) $(CFLAGS) -o $@ $^ $(LIBLD)

clean:
	rm -f *.o *.so UnionDec
