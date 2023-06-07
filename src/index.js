import ReactDOM from "react-dom/client";
import { HashRouter, BrowserRouter, Routes, Route, useNavigate } from "react-router-dom";
import React from 'react';
import './index.css';
import './App.css';
import Qcm from './composants/Qcm';
import Create from "./composants/Create";
import Header from "./composants/Header";
import ChoixQcm from "./composants/ChoixQcm";
import User from "./composants/User";


const root = ReactDOM.createRoot(document.getElementById('root'));

root.render(
  <HashRouter>
    <Routes>
      <Route path="/" element={<Header />} />
      <Route path="/Qcm" element={<Qcm />} />
      <Route path="/Create" element={<Create />} />
      <Route path="/ChoixQcm" element={<ChoixQcm />} />
      <Route path="/User" element={<User/>} />

    </Routes>
  </HashRouter>

);


