    processor 6502    
    
    org     $8000           ;Start of left cartridge area

    include "global.inc"
    include "atari.inc"
    include "draw.inc"
    include "draw-sprite.inc"
    include "init.inc"

; ==========================================
; Program start
; ==========================================
Start:
    jsr Initialize
    
    ; test buffer 1
    lda #$22
    sta Buffer1
    sta Buffer1+80
    lda #$21
    sta Buffer2
    sta Buffer2+80
    
    ;----------------------------------
    ; Draw Sprite
    ;----------------------------------
    lda #2
    sta CurrX
    sta OldX
    lda #10
    sta CurrY
    sta OldY
    
    lda CurrX
    sta SPR_X
    lda CurrY
    sta SPR_Y
    lda #<Rocket
    sta SPR_PTR
    lda #>Rocket
    sta SPR_PTR+1

    jsr SetBuffer1
    ;jsr DrawSprite_16x16_XOR
    jsr SetBuffer2
    ;jsr DrawSprite_16x16_XOR
    jsr SwitchScreenBuffer
    
; infinite loop
Begin

    ; Wait for screen
    lda RTCLOK2
WaitVBL
    cmp RTCLOK2
    beq WaitVBL

    ldx  #1
Pause1:
    ldy #255
Pause2:
    lda OldX;
    sta SPR_X
    lda OldY;
    sta SPR_Y
    dey
    bne Pause2
    
    dex
    bne Pause1
        
    jsr DrawSprite_16x16_XOR
    jsr DrawSprite_16x16_XOR
    jsr DrawSprite_16x16_XOR
    jsr DrawSprite_16x16_XOR
    jsr DrawSprite_16x16_XOR
    jsr DrawSprite_16x16_XOR
    jsr DrawSprite_16x16_XOR
    jsr DrawSprite_16x16_XOR
    jsr DrawSprite_16x16_XOR

; store position
    lda CurrX
    sta OldX;
    lda CurrY
    sta OldY;
    
    ; Increase X,Y coordinates
    ;inc CurrX
    inc CurrY
    inc CurrY
    ; Check X,Y coordinates out of screen
    lda CurrX
    cmp #36
    bcc CheckY      ; If X < 128, skip reset
    lda #0
    sta CurrX

CheckY
    lda CurrY
    cmp #80
    bcc DrawContinue     ; If Y < 64, skip reset
    lda #0
    sta CurrY

DrawContinue
    lda CurrX
    sta SPR_X
    lda CurrY
    sta SPR_Y
    
    jsr DrawSprite_16x16_XOR
    jsr DrawSprite_16x16_XOR
    jsr DrawSprite_16x16_XOR
    jsr DrawSprite_16x16_XOR
    jsr DrawSprite_16x16_XOR
    jsr DrawSprite_16x16_XOR
    jsr DrawSprite_16x16_XOR
    jsr DrawSprite_16x16_XOR
    jsr DrawSprite_16x16_XOR
    
    jsr SwitchScreenBuffer

End
    nop
    jmp     Begin

; ==========================================
;Graphics data
; ==========================================
    
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

