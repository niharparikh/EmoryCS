all: manage compute report

manage: manage.c ds.h
	gcc manage.c -o manage

compute: compute.c ds.h
	gcc compute.c -o compute

report: report.c ds.h
	gcc report.c -o report

clean:
	rm manage compute report