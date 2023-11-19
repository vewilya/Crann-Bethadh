import { writable, readable } from 'svelte/store';

export const pluginParams = writable({
    convolution: 0.4,
    feedback: 0.4,
    drive: 0.4,
    satType: 0,
});