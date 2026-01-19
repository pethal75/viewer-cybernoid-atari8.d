    processor 6502    
    
    org     $8000           ;Start of left cartridge area

    include "atari.inc"

    include "global.inc"
    include "init.inc"
    include "draw.inc"
    include "draw-sprite.inc"
    include "game-draw.inc"

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
    lda #<Enemy11
    sta SPR_PTR
    lda #>Enemy11
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

    ldx  #5
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
    
    lda OldX
    sta TmpX
    jsr DrawSprite_16x16_XOR
    lda OldX
    adc #5
    sta OldX
    sta SPR_X
    jsr DrawSprite_16x16_XOR
    lda OldX
    adc #5
    sta OldX
    sta SPR_X
    jsr DrawSprite_16x16_XOR
    lda OldX
    adc #5
    sta OldX
    sta SPR_X
    jsr DrawSprite_16x16_XOR
    lda OldX
    adc #5
    sta OldX
    sta SPR_X
    jsr DrawSprite_16x16_XOR
    lda OldX
    adc #5
    sta OldX
    sta SPR_X
    jsr DrawSprite_16x16_XOR
    lda OldX
    adc #5
    sta OldX
    sta SPR_X
    jsr DrawSprite_16x16_XOR
    lda OldX
    adc #5
    sta OldX
    sta SPR_X
    jsr DrawSprite_16x16_XOR
    lda TmpX
    sta OldX

; store position
    lda CurrX
    sta OldX;
    lda CurrY
    sta OldY;
    
    ; Increase X,Y coordinates
    ;inc CurrX
    ;inc CurrY
    inc CurrY
    ; Check X,Y coordinates out of screen
    lda CurrX
    cmp #36
    bcc CheckY      ; If X < 128, skip reset
    lda #0
    sta CurrX

CheckY
    lda CurrY
    cmp #96
    bcc DrawContinue     ; If Y < 64, skip reset
    lda #0
    sta CurrY

DrawContinue
    lda CurrX
    sta SPR_X
    lda CurrY
    sta SPR_Y
    
    lda CurrX
    sta TmpX
    jsr DrawSprite_16x16_XOR
    lda CurrX
    adc #5
    sta CurrX
    sta SPR_X
    jsr DrawSprite_16x16_XOR
    lda CurrX
    adc #5
    sta CurrX
    sta SPR_X
    jsr DrawSprite_16x16_XOR
    lda CurrX
    adc #5
    sta CurrX
    sta SPR_X
    jsr DrawSprite_16x16_XOR
    lda CurrX
    adc #5
    sta CurrX
    sta SPR_X
    jsr DrawSprite_16x16_XOR
    lda CurrX
    adc #5
    sta CurrX
    sta SPR_X
    jsr DrawSprite_16x16_XOR
    lda CurrX
    adc #5
    sta CurrX
    sta SPR_X
    jsr DrawSprite_16x16_XOR
    lda CurrX
    adc #5
    sta CurrX
    sta SPR_X
    jsr DrawSprite_16x16_XOR
    lda TmpX
    sta CurrX

    lda #<Enemy10
    cmp SPR_PTR
    bne Sprite1
    lda #<Enemy11
    sta SPR_PTR
    lda #>Enemy11
    sta SPR_PTR+1
    jmp Continue
Sprite1:
    lda #<Enemy10
    sta SPR_PTR
    lda #>Enemy10
    sta SPR_PTR+1
Continue:

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

