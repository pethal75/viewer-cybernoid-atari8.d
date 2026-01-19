    processor 6502    
    
    org     $8000           ;Start of left cartridge area

    include "atari.inc"
    
    include "global.inc"
    include "draw.inc"
    include "draw-sprite.inc"
    include "init.inc"
    

; ==========================================
; Program start
; ==========================================
Start:
    jsr Initialize
    
    ; test buffer 1
    lda #34
    sta Buffer1
    sta Buffer1+80
    
    ; enable DMI
    lda     #$22            ;Enable DMA
    sta     SDMCTL
    
    ;----------------------------------
    ; Actual screen buffer set to Buffer1
    ;----------------------------------
    lda #<Buffer1
    sta ActualBufferAddr
    lda #>Buffer1
    sta ActualBufferAddr + 1
    
    ;----------------------------------
    ; Draw Sprite
    ;----------------------------------
    lda #39
    sta SPR_X
    lda #1
    sta SPR_Y
    
    lda #<Rocket
    sta SPR_PTR
    lda #>Rocket
    sta SPR_PTR+1

; infinite loop
Begin

    ; Wait for screen
    lda RTCLOK2
WaitVBL
    cmp RTCLOK2
    beq WaitVBL
    
    jsr DrawSprite_16x16_XOR
    jsr DrawSprite_16x16_XOR
    jsr DrawSprite_16x16_XOR
    jsr DrawSprite_16x16_XOR
    jsr DrawSprite_16x16_XOR
    jsr DrawSprite_16x16_XOR
    jsr DrawSprite_16x16_XOR
    jsr DrawSprite_16x16_XOR
    jsr DrawSprite_16x16_XOR
    jsr DrawSprite_16x16_XOR
    
    ;----------------------------------
    ; Draw rectangle
    ;----------------------------------
    lda #$00
    sta COLOR_V
    ;jsr DrawRect    ; Call routine
    
    ; Increase X,Y coordinates
    inc RECT_X
    inc RECT_Y
    inc RECT_Y
    ; Check X,Y coordinates out of screen
    lda RECT_X
    cmp #36
    bcc CheckY      ; If X < 128, skip reset
    lda #0
    sta RECT_X

CheckY
    lda RECT_Y
    cmp #80
    bcc DrawContinue     ; If Y < 64, skip reset
    lda #0
    sta RECT_Y

DrawContinue
    jsr DrawSprite_16x16_XOR
    jsr DrawSprite_16x16_XOR
    jsr DrawSprite_16x16_XOR
    jsr DrawSprite_16x16_XOR
    jsr DrawSprite_16x16_XOR
    jsr DrawSprite_16x16_XOR
    jsr DrawSprite_16x16_XOR
    jsr DrawSprite_16x16_XOR
    jsr DrawSprite_16x16_XOR
    jsr DrawSprite_16x16_XOR

    
    ;jsr DrawRect    ; Call routine
    ;jsr DrawRect    ; Call routine
 
End
    nop
    jmp     Begin

; ==========================================
;Graphics data
; ==========================================
    align $100   ; ANTIC can only count to $FFF
    
Sprites:
    include "sprites.inc"


; ==========================================
;Cartridge footer
; ==========================================
    org     CARTCS
    .word 	Start	; cold start address
    .byte	$00	; 0 == cart exists
    .byte	$04	; boot cartridge
    .word	Start	; start

