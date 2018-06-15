typedef struct {
  uint8_t palette_cgb:3; //cgb only
  bool tile_bank:1; //cgb only
  bool palette:1; //palette select
  bool x_flip:1;
  bool y_flip:1;
  bool bg_priority:1;
} sprite_flags_t;

typedef struct {
  uint8_t pos_y;
  uint8_t pos_x;
  uint8_t tile;
  sprite_flags_t flags;
} sprite_t;

sprite_t sprite_get(uint8_t index);
