#ifndef MAPS_H
#define MAPS_H

class Maps
{
public:
	Maps(unsigned long src, unsigned long dest, unsigned long len) {
		src_start = src;
		dest_start = dest;
		length = len;
	}

	unsigned long src_start;
	unsigned long dest_start;
	unsigned long length;
};

#endif