CPPFLAGS=`root-config --cflags` -I/usr/local/root/include
LDFLAGS=`root-config --libs` -lMinuit
all: SkimerBoost_tt
#all: SkimerBoost_mt  SkimerBoost_et SkimerBoost_mm SkimerBoost_tt
#SkimerBoost_mt: SkimerBoost_mt.cc
#	g++ $(CPPFLAGS) $(LDFLAGS) -o $@ $^
#SkimerBoost_et: SkimerBoost_et.cc
#	g++ $(CPPFLAGS) $(LDFLAGS) -o $@ $^
#SkimerBoost_mm: SkimerBoost_mm.cc
#	g++ $(CPPFLAGS) $(LDFLAGS) -o $@ $^
SkimerBoost_tt: SkimerBoost_tt.cc
	g++ $(CPPFLAGS) $(LDFLAGS) -o $@ $^

