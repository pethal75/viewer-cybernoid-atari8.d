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

SpritesList = $7000
Score 	= $7100
    
CurrX 	= $7101
CurrY 	= $7102
OldX	= $7103
OldY	= $7104
TmpX	= $7105
TmpY	= $7106
        
DlListPtr = $7500
DlListScreenAddr = $7504

; ==========================================
; Other constants
; ==========================================
RTCLOK2 = $14
    

; ==========================================
; Routines
; ==========================================
SwitchScreenBuffer:
    lda ActualBufferAddr + 1
    cmp #>Buffer1
    beq SetBuffer2
    
SetBuffer1:
    lda #<Buffer1
    sta ActualBufferAddr
    lda #>Buffer1
    sta ActualBufferAddr + 1

    lda #<Buffer2
    sta DlListScreenAddr
    lda #>Buffer2
    sta DlListScreenAddr + 1
    rts

SetBuffer2:
    lda #<Buffer2
    sta ActualBufferAddr
    lda #>Buffer2
    sta ActualBufferAddr + 1

    lda #<Buffer1
    sta DlListScreenAddr
    lda #>Buffer1
    sta DlListScreenAddr + 1
    rts

; ==========================================
;Display list data
; ==========================================
dlist
    .byte $70,$70,$70
    .byte $4d,#<Buffer1, #>Buffer1
    REPEAT 95
    .byte $0d
    REPEND
    .byte $41,$00,$10
dlistend equ .

