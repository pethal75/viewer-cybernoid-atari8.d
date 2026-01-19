; ==========================================
; Screen buffers
; ==========================================
Buffer1 = $3000
Buffer2 = $4000

ActualBufferAddr = $D0

; ==========================================
; Input parameters
; ==========================================
RECT_X  = $c0       ; Input X (0-159)
RECT_Y  = $c1       ; Input Y (0-96)

SCR_PTR = $c2

SPR_X    = $c0    ; X position in BYTES (pixel_x / 4)
SPR_Y    = $c1    ; Y position in LINES
SPR_PTR  = $c4    ; 2 bytes

TMP_PTR = $c6
TMP_LO  = $c7       ; New Temp var for math
TMP_HI  = $c8       ; New Temp var for math

; ==========================================
; Game engine data
; ==========================================

SpritesList
    REPEAT 256
    .byte $00
    REPEND
Score
    .byte $00

; ==========================================
; Other constants
; ==========================================
RTCLOK2 = $14


