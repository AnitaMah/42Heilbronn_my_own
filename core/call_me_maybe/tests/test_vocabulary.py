from src.vocabulary import decode_bpe_token, encode_bpe_token


def test_ascii_letters_roundtrip():
    for text in ["hello", "fn_add_numbers", "Shrek42", "-3.14"]:
        assert decode_bpe_token(encode_bpe_token(text)) == text


def test_space_is_not_identity_mapped():
    # GPT-2 byte-level BPE never emits a literal space in a vocab key -- it's
    # remapped (conventionally to 'Ġ'). Make sure our table does the same.
    encoded = encode_bpe_token(" hello")
    assert " " not in encoded
    assert decode_bpe_token(encoded) == " hello"


def test_unrecognized_characters_pass_through(make_model, make_vocabulary):
    # special tokens like <|endoftext|> aren't byte-encoded in real tokenizers;
    # decode_bpe_token should leave characters it doesn't recognize untouched.
    assert decode_bpe_token("<|endoftext|>") == "<|endoftext|>"


def test_vocabulary_loads_from_fake_model(make_model, make_vocabulary):
    model = make_model()
    vocabulary = make_vocabulary(model)
    assert len(vocabulary) == model.vocab_size
    # every piece we registered decodes back to itself through the full pipeline
    for text, token_id in model.text_to_id.items():
        assert vocabulary.text_of(token_id) == text
