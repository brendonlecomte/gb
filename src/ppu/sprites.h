typedef struct {
  bool bg_priority:1;
  bool y_flip:1;
  bool x_flip:1;
  bool palette:1;
  bool tile_bank:1; //cgb only
  uint8_t palette_cgb:3; //cgb only
} sprite_flags_t;

typedef struct {
  uint8_t pos_y;
  uint8_t pos_x;
  uint8_t tile;
  sprite_flags_t flags;
} sprite_t;
