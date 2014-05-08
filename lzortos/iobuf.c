#define IOBUF_RECV_BUFLEN	16
#define IOBUF_TRAN_BUFLEN	100

struct cmnbuf {
	unsigned int produced;
	unsigned int consumed;
	unsigned int len;
	char *start;
};

struct iobuf {
	struct cmnbuf tx;
	struct cmnbuf rx;
};

static char recv_buf[IOBUF_RECV_BUFLEN];
static char tran_buf[IOBUF_TRAN_BUFLEN];

static struct iobuf buf;

static void cmnbuf_init(struct cmnbuf *buf, char *bufstart, const unsigned int len)
{
	buf->produced = buf->consumed = 0;
	buf->len = len;
	buf->start = bufstart;
}

static void tx_init(char *bufstart, const unsigned int len)
{
	cmnbuf_init(&buf.tx, bufstart, len);
}

static void tx_produce(const char c)
{
	/* Is there a free byte in the transmission buffer? */
	if (buf.tx.produced < buf.tx.len) {
		/* Write to the transmission buffer */
		buf.tx.start[buf.tx.produced] = c;
		buf.tx.produced += 1;
	}
}

static void tx_consume(void)
{
	/* This is where the write function of the IO device driver must be called */
	/* for example uart_putc() */
}

static void rx_init(char *bufstart, const unsigned int len)
{
	cmnbuf_init(&buf.rx, bufstart, len);
}

static void rx_produce(void)
{
	/* This is where the read function of the IO device driver must be called */
	/* for example uart_getc() */
}

static char rx_consume(void)
{
	char c;
	/* Is there a byte to be read from the receive buffer? */
	if (buf.rx.consumed < buf.rx.produced) {
		/* Read from the receive buffer */
		c = buf.rx.start[buf.rx.consumed];
		if (buf.rx.consumed < buf.rx.len)
			buf.rx.consumed += 1;
	}
	return c;
}

void iobuf_init(void)
{
	tx_init(tran_buf, IOBUF_TRAN_BUFLEN);
	rx_init(recv_buf, IOBUF_RECV_BUFLEN);
}

/* Write a byte to be transmitted */
void iobuf_putc(const char c)
{
	tx_produce(c);
}

/* Read a byte received */
char iobuf_getc(void)
{
	return rx_consume();
}

/* Perform actual transmission and reception */
void iobuf_update(void)
{
	/* Transmission */

	/* Check if there is a byte */
	if (buf.tx.consumed < buf.tx.produced) {
		tx_consume();
		buf.tx.consumed += 1;
	} else {
		buf.tx.produced = buf.tx.consumed = 0;
	}

	/* Reception */

	if (buf.rx.produced == buf.rx.consumed)
		buf.rx.produced = buf.rx.consumed = 0;

	rx_produce();
	if (buf.rx.produced < buf.rx.len)
		buf.rx.produced += 1;
}

int main(int argc, char *argv[])
{
	return 0;
}
