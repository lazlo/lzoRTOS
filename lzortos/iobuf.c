#define IOBUF_RECV_BUFLEN	16
#define IOBUF_TRAN_BUFLEN	100

struct cmnbuf {
	unsigned int head; /* produced */
	unsigned int tail; /* consumed */
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
	buf->head = buf->tail = 0;
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
	if (buf.tx.head < buf.tx.len) {
		/* Write to the transmission buffer */
		buf.tx.start[buf.tx.head] = c;
		buf.tx.head += 1;
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
	if (buf.rx.tail < buf.rx.head) {
		/* Read from the receive buffer */
		c = buf.rx.start[buf.rx.tail];
		if (buf.rx.tail < buf.rx.len)
			buf.rx.tail += 1;
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
	if (buf.tx.tail < buf.tx.head) {
		tx_consume();
		buf.tx.tail += 1;
	} else {
		buf.tx.head = buf.tx.tail = 0;
	}

	/* Reception */

	if (buf.rx.head == buf.rx.tail)
		buf.rx.head = buf.rx.tail = 0;

	rx_produce();
	if (buf.rx.head < buf.rx.len)
		buf.rx.head += 1;
}

int main(int argc, char *argv[])
{
	return 0;
}
