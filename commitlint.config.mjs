export default {
    rules: {
        'type-enum': [2, 'always', ['ADD', 'FIX', 'UPDATE', 'REMOVE']],
        'type-case': [2, 'always', 'upper-case'],
        'body-min-length': [2, 'always', 10],
    },
    parserPreset: {
        parserOpts: {
            headerPattern: /^(\w+):\s(.+)$/,
            headerCorrespondence: ['type', 'subject'],
        },
    },
};
