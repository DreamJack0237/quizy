import ReactDOM from "react-dom/client";
import { BrowserRouter, Routes, Route } from "react-router-dom";
import React from 'react';
import './index.css';
import './App.css';
import Qcm from './composants/Qcm';
import Create from "./composants/Create";
import Header from "./composants/Header";


const root = ReactDOM.createRoot(document.getElementById('root'));

root.render(
  <BrowserRouter>
    <Routes>
      <Route path="/." element={<Header />} />
      <Route path="/Qcm" element={<Qcm />} />
      <Route path="/Create" element={<Create />} />

    </Routes>
  </BrowserRouter>

);


