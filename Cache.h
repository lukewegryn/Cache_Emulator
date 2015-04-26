class Cache{
	private:
		enum cacheSize {K_1 = 1024, K_4 = 4096, K_64 = 65536, K_128 = 131072};
		enum blockSize {B_8 = 8, B_16 = 16, B_32 = 32, B_128 = 128};
		enum mapType {DM, Way_2, Way_4, FA};
		enum writePolicy {WB, WT};
		enum result {HIT, MISS};
	public:
};